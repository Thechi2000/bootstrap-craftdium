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
	// Contains the data needed to start a download
	struct Download
	{
		const char* url;
		const char* filename;
	};

	~Downloader();

	// Starts the downloading thread
	void start();
	// Adds a download to the queue (even if the thread is already running)
	void queue(const char* url, const char* filename);
	void queue(Download download);
	// Immediatly terminate the downloading thread
	void stop();

	// The unique instance of this class
	// Must be used to launch 
	static Downloader instance;

private:
	friend int __updateDownloaderProgressBar(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

	using ProgressBar::setCurrentValue;
	using ProgressBar::setMaxValue;

	Downloader();
	void threadFunc();

	std::queue<Download> m_queuedDownloads;
	sf::Mutex m_queueMutex;
	sf::Thread m_downloadThread;
	bool m_isRunning;
};

// Downloads the file from the given url to the given file
// Blocks until the download is finished (consider using Downloader instead)
void downloadFile(const char* url, const char* fname);
