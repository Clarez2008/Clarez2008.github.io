#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<vector>
#include<windows.h>
#include<io.h>
using namespace std;
#define MAX_PATH 80
std::string to_utf8(const wchar_t* buffer,int len) {
	int nChars =::WideCharToMultiByte(CP_UTF8,0,buffer,len,NULL,0,NULL,NULL);
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
std::string to_utf8(const std::wstring& str) {
	return to_utf8(str.c_str(),(int)str.size());
}
void getFiles( string path, string path2, vector<string>& files );
int main() {
	vector<string> files;
	char   buffer[MAX_PATH];
	getcwd(buffer, MAX_PATH);
	string filePath;
	filePath.assign(buffer).append("\\");
	////获取该路径下的所有文件
	getFiles(filePath,"", files );
	int size = files.size();
	for (int i = 0; i < size; i++) {
		cout<<files[i].c_str()<<endl;
	}
	freopen("book.html","w",stdout);
	printf("<!DOCTYPE html>");
	printf("<html>\n");
	printf("	<head>\n");
	printf("		<meta charset=\"utf-8\">\n");
	printf("	</head>\n");
	printf("	<body>\n");
	printf("		<table>\n");
	for(int i=0; i<size; i++) {
		printf("			<tr>\n");
			
		cout<<"				<td>"<<files[i]<<"</td>"<<endl;
		printf("			</tr>\n");
	}
	printf("		</table>\n");
	printf("	</body>\n");
	printf("</html>\n");
	return 0;
}
void getFiles( string path, string path2, vector<string>& files ) {
	//文件句柄
	long   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p,p2;
	if((hFile = _findfirst(p.assign(path).append(path2).append("*").c_str(),&fileinfo)) !=  -1) {
		do {
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR)) {
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\"),p2.assign(fileinfo.name).append("\\"), files );
			} else {
				files.push_back(p.assign(path2).append(fileinfo.name) );  //这一行可以给出相对路径
				//files.push_back(p.assign(fileinfo.name) );  //这一行可以给出文件名
			}
		} while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
