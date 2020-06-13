#!/usr/bin/env python
import os,sys,chardet,codecs
def change_file_charset(file_name):
    if file_name == "":
        return False;
    f = open(file_name)
    s = f.read()
    f.close()
    old_charset = chardet.detect(s)['encoding']
    print "old_charset:",old_charset
    if old_charset == 'UTF-8-SIG':
        print ('file_name:%s is UTF-8 BOM' % file_name)
        return True
    if old_charset == '' or old_charset == None:
        print ('file_name:%s has no encoding' % file_name)
        f = open('no_encoding.txt','a+')
        f.writelines(file_name)
        f.close()
        return False
    print 'remove file:',file_name
    os.remove(file_name)
    u = s.decode(old_charset)
    f = open(file_name,'w')
    s = u.encode('utf_8_sig')
    f.write(s)
    f.close()
    print ('file_name:%s has wrrite utf-8 BOM' % file_name)
    return True
    
def exist_bom(file_name):
    f = open(file_name)
    s = f.read(3)
    f.close()
    if s == codecs.BOM_UTF8:
        return True
    return False

def dirlist(path, allfile):
    filelist =  os.listdir(path)

    for filename in filelist:
        filepath = os.path.join(path, filename)
        if os.path.isdir(filepath):
            dirlist(filepath, allfile)
        else:
            allfile.append(filepath)
    return allfile 

if __name__ == '__main__':
    path = sys.argv[1]
    #change_file_charset(file_name)
    if os.path.isdir(path):
        all_file = []
        dirlist(path,all_file)
        for file_name in all_file:
            suffix = file_name.split('.')[-1]
            if suffix == 'cpp' or suffix == 'c' or suffix == 'hpp' or suffix == 'h':
                change_file_charset(file_name)

        print 'all_file num:', len(all_file)
    else:
        change_file_charset(path)
