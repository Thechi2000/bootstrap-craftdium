#include "Downloader.h"
#include <curl/curl.h>
#include <iostream>
#pragma warning(disable : 4996)

using namespace std;

Downloader::Downloader() :
	m_queuedDownloads(),
	m_queueMutex(),
	m_downloadThread(&Downloader::threadFunc, this),
	m_isRunning(false)
{
}
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

void Downloader::queue(Download download)
{
	m_queueMutex.lock();
	m_queuedDownloads.push(download);
	m_queueMutex.unlock();
}

void Downloader::threadFunc()
{
	std::queue<Download> downloadsQueue;

	while(true)
	{
		m_queueMutex.lock();
		
		while(!m_queuedDownloads.empty())
		{
			downloadsQueue.push(m_queuedDownloads.front());
			m_queuedDownloads.pop();
		}

		m_queueMutex.unlock();

		while(!downloadsQueue.empty())
		{
			auto download = downloadsQueue.front();
			downloadsQueue.pop();

			downloadFile(download.url, download.filename);
		}

		Sleep(100);
	}
}

Downloader Downloader::instance;

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
	res = curl_easy_perform(curl);
	fclose(fp);
}
