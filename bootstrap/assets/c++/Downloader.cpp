#include "Downloader.h"
#include <curl/curl.h>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#pragma warning(disable : 4996)

using namespace std;
using namespace sf;

long Downloader::fileSize(const char* url)
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
	curl_easy_setopt(curl, CURLOPT_URL, url);

	res = curl_easy_perform(curl);

	double length;
	curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &length);

	return length;
}

Downloader::Downloader() :
	ProgressBar(0, 0, 100, 20),
	m_queuedDownloads(),
	m_queueMutex(),
	m_downloadedFileSize(0),
	m_downloadThread(&Downloader::threadFunc, this),
	m_isRunning(false)
{}
Downloader::~Downloader()
{
	stop();
}

void Downloader::start()
{
	if(!m_isRunning)
	{
		m_downloadThread.launch();
		m_isRunning = true;
	}
	else
		cout << "[WARNING: Tried to start the Downloader when it was already running";
}
void Downloader::stop()
{
	if(m_isRunning)
	{
		m_downloadThread.terminate();
		m_isRunning = false;
	}
	else
		cout << "[WARNING: Tried to stop the Downloader when it was not running";
}

void Downloader::queue(const char* url, const char* filename)
{
	m_queuedDownloads.push({ url, filename, fileSize(url)});
}

void Downloader::threadFunc()
{
	std::queue<Download> downloadsQueue;

	m_queueMutex.lock();

	long long total = 0;
	while(!m_queuedDownloads.empty())
	{
		auto& down = m_queuedDownloads.front();
		total += down.fileSize;
		downloadsQueue.push(down);
		m_queuedDownloads.pop();
	}
	setMaxValue(total);

	m_queueMutex.unlock();

	while(!downloadsQueue.empty())
	{
		auto& download = downloadsQueue.front();
		downloadsQueue.pop();

		downloadFile(download.url, download.filename);

		m_downloadedFileSize += download.fileSize;
	}
}

Downloader Downloader::instance;

int __updateDownloaderProgressBar(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	Downloader::instance.setCurrentValue(Downloader::instance.m_downloadedFileSize + dlnow);
	return 0;
}

void downloadFile(const char* url, const char* fname)
{
	CURL* curl;
	FILE* fp;
	CURLcode res;
	curl = curl_easy_init();

	fp = fopen(fname, "wb");
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
	curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, __updateDownloaderProgressBar);
	res = curl_easy_perform(curl);
	fclose(fp);
}
