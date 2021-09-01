#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <curl/curl.h>
#include <queue>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include "ProgressBar.h"

class Downloader : public ProgressBar
{
public:

	~Downloader();

	// Starts the downloading thread
	void start();
	// Adds a download to the queue
	// If the download has already start, this file won't be downloaded
	void queue(const char* url, const char* filename);
	// Immediatly terminate the downloading thread
	void stop();

	// The unique instance of this class
	// Must be used to launch 
	static Downloader instance;

private:
	struct Download
	{
		const char* url;
		const char* filename;
		long fileSize;
	};

	friend int __updateDownloaderProgressBar(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
	static long fileSize(const char* url);

	using ProgressBar::setCurrentValue;
	using ProgressBar::setMaxValue;

	Downloader();
	void threadFunc();

	std::queue<Download> m_queuedDownloads;
	sf::Mutex m_queueMutex;
	long long m_downloadedFileSize;
	sf::Thread m_downloadThread;
	bool m_isRunning;
};

// Downloads the file from the given url to the given file
// Blocks until the download is finished (consider using Downloader instead)
void downloadFile(const char* url, const char* fname);
