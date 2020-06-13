#ifndef RECOREDFILEBROWSER_H
#define RECOREDFILEBROWSER_H
#include <list>
#include <QString>

class RecoredFileBrowser
{
public:
    ~RecoredFileBrowser(){}
    static RecoredFileBrowser* getInstance(){
        static RecoredFileBrowser instance;
        return &instance;
    }

    void add_recored_fielbrowser(QString msgId){
        _recored_file_browser.push_back(msgId);
    }

    void delete_recored_filebrowser(QString msgId){
        _recored_file_browser.remove(msgId);
    }

    void clear_recored_filebrowser(){
        _recored_file_browser.clear();
    }
public:
    std::list<QString>   _recored_file_browser;
private:
    RecoredFileBrowser(){}
    RecoredFileBrowser(const RecoredFileBrowser& obj) = delete;
    RecoredFileBrowser& operator=(const RecoredFileBrowser& obj) = delete;
};

#endif // RECOREDFILEBROWSER_H
