#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<vector>
#include<windows.h>
#include<io.h>
using namespace std;
#define MAX_PATHH 80

void getFiles( string path, string path2, vector<string>& files );
string to_utf8(const wchar_t* buffer,int len){
        int nChars =::WideCharToMultiByte(
                CP_UTF8,
                0,
                buffer,
                len,
                NULL,
                0,
                NULL,
                NULL);
        if(nChars ==0)return"";

        string newbuffer;
        newbuffer.resize(nChars);
        ::WideCharToMultiByte(
                CP_UTF8,
                0,
                buffer,
                len,
                const_cast<char*>(newbuffer.c_str()),
                nChars,
                NULL,
                NULL);

        return newbuffer;
}
int main() {
	string a;cin>>a;
	vector<wstring> files;
	char   buffer[MAX_PATHH];
	getcwd(buffer, MAX_PATHH);
	string filePath;
	filePath.assign(buffer).append("\\");
	//��ȡ��·���µ������ļ�
	getFiles(filePath,"", files );
	int size = files.size();

//	freopen(a.c_str(),"w",stdout);
	cout<<to_utf8(L"<!DOCTYPE html>\n",16);
	cout<<to_utf8(L"<html>\n",7);
	cout<<to_utf8(L"	<head>\n",8);
	cout<<to_utf8(L"		<meta charset=\"utf-8\">\n",27);
	cout<<to_utf8(L"	</head>\n",9);
	cout<<to_utf8(L"	<body>\n",8);
	cout<<to_utf8(L"		<table>\n",10);
	for(int i=0; i<size; i++) {
		cout<<to_utf8(L"			<tr>\n",8);
		cout<<to_utf8(L"				<td><a href=\"",17)<<files[i]<<to_utf8(L"\" download >",12)<<to_utf8(files[i].c_str,(int)(files[i].size()))<<to_utf8("</a></td>",9)<<endl;
		cout<<to_utf8(L"			</tr>\n",9);
	}
	cout<<to_utf8(L"		</table>\n",11);
	cout<<to_utf8(L"	</body>\n",9);
	cout<<to_utf8(L"</html>\n",8);
	return 0;
}
void getFiles( string path, string path2, vector<wstring>& files ) {
	//�ļ����
	long   hFile   =   0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p,p2;
	if((hFile = _findfirst(p.assign(path).append(path2).append("*").c_str(),&fileinfo)) !=  -1) {
		do {
			//�����Ŀ¼,����֮
			//�������,�����б�
			if((fileinfo.attrib &  _A_SUBDIR)) {
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\"),p2.assign(fileinfo.name).append("\\"), files );
			} else {
//				files.push_back(p.assign(path2).append(fileinfo.name) );  //��һ�п��Ը������·��
				p.assign(fileinfo.name);
				if(p!="build.exe"){
					
					files.push_back(p);  //��һ�п��Ը����ļ���
				}
			}
		} while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
