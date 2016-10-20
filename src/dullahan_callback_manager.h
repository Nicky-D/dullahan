/*
    @brief Dullahan - a headless browser rendering engine
           based around the Chromium Embedded Framework
    @author Callum Prentice 2015

    LICENSE FILE TO GO HERE
*/

#ifndef _DULLAHAN_CALLBACK_MANAGER
#define _DULLAHAN_CALLBACK_MANAGER

#include <functional>

#include "dullahan.h"

class dullahan_callback_manager
{
    public:
        void setOnAddressChangeCallback(std::function<void(const std::string url)> callback);
        void onAddressChange(const std::string url);

        void setOnConsoleMessageCallback(std::function<void(const std::string message, const std::string source, int line)>
                                         callback);
        void onConsoleMessage(const std::string messgae, const std::string source, int line);

        void setOnCursorChangedCallback(std::function<void(const dullahan::ECursorType type, const unsigned int cursor)>
                                        callback);
        void onCursorChanged(const dullahan::ECursorType type, const unsigned int cursor);

        void setOnCustomSchemeURLCallback(std::function<void(const std::string url)> callback);
        void onCustomSchemeURL(const std::string url);

        void setOnHTTPAuthCallback(
            std::function<bool(const std::string host, const std::string realm, std::string& username, std::string& password)>
            callback);
        bool onHTTPAuth(const std::string host, const std::string realm, std::string& username, std::string& password);

        void setOnLoadEndCallback(std::function<void(int status)> callback);
        void onLoadEnd(int status);

        void setOnLoadErrorCallback(std::function<void(int status, const std::string error_text)> callback);
        void onLoadError(int status, const std::string error_text);

        void setOnLoadStartCallback(std::function<void()> callback);
        void onLoadStart();

        void setOnNavigateURLCallback(std::function<void(const std::string url, const std::string target)> callback);
        void onNavigateURL(const std::string url, const std::string target);

        void setOnPageChangedCallback(
            std::function<void(const unsigned char* pixels, int x, int y, int width, int height, bool is_popup)> callback);
        void onPageChanged(const unsigned char* pixels, int x, int y, int width, int height, bool is_popup);

        void setOnStatusMessageCallback(std::function<void(const std::string message)> callback);
        void onStatusMessage(const std::string message);

        void setOnRequestExitCallback(std::function<void()> callback);
        void onRequestExit();

        void setOnTitleChangeCallback(std::function<void(const std::string title)> callback);
        void onTitleChange(const std::string title);

        void setOnPdfPrintFinishedCallback(std::function<void(const std::string path, bool ok)> callback);
        void onPdfPrintFinished(const std::string path, bool ok);

        void setOnFileDownloadCallback(std::function<void(const std::string filename)> callback);
        void onFileDownload(const std::string filename);

        void setOnFileDialogCallback(std::function<const std::string()> callback);
        const std::string onFileDialog();

    private:
        std::function<void(const std::string)> mOnAddressChangeCallbackFunc;
        std::function<void(const std::string, const std::string, int)> mOnConsoleMessageCallbackFunc;
        std::function<void(const dullahan::ECursorType type, const unsigned int cursor)> mOnCursorChangedCallbackFunc;
        std::function<void(const std::string)> mOnCustomSchemeURLCallbackFunc;
        std::function<bool(const std::string, const std::string, std::string&, std::string&)> mOnHTTPAuthCallbackFunc;
        std::function<void(int)> mOnLoadEndCallbackFunc;
        std::function<void(int, const std::string error_text)> mOnLoadErrorCallbackFunc;
        std::function<void()> mOnLoadStartCallbackFunc;
        std::function<void(const std::string, const std::string)> mOnNavigateURLCallbackFunc;
        std::function<void(const unsigned char*, int, int, int, int, bool)> mOnPageChangedCallbackFunc;
        std::function<void(const std::string)> mOnStatusMessageCallbackFunc;
        std::function<void()> mOnRequestExitCallbackFunc;
        std::function<void(const std::string)> mOnTitleChangeCallbackFunc;
        std::function<void(const std::string, bool)> mOnPdfPrintFinishedCallbackFunc;
        std::function<void(const std::string)> mOnFileDownloadCallbackFunc;
        std::function<const std::string()> mOnFileDialogCallbackFunc;
};

#endif //_DULLAHAN_CALLBACK_MANAGER
