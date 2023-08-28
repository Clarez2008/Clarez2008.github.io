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
int main() {
	string a;cin>>a;
	vector<string> files;
	char   buffer[MAX_PATHH];
	getcwd(buffer, MAX_PATHH);
	string filePath;
	filePath.assign(buffer).append("\\");
	//获取该路径下的所有文件
	getFiles(filePath,"", files );
	int size = files.size();

	freopen(a.c_str(),"w",stdout);
	printf("<!DOCTYPE html>\n");
	printf("<html>\n");
	printf("	<head>\n");
	printf("		<meta charset=\"utf-8\">\n");
	printf("	</head>\n");
	printf("	<body>\n");
	printf("		<table>\n");
	for(int i=0; i<size; i++) {
		printf("			<tr>\n");
		cout<<"				<td><a href=\""<<files[i]<<"\" download >"<<files[i]<<"</a></td>"<<endl;
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
//				files.push_back(p.assign(path2).append(fileinfo.name) );  //这一行可以给出相对路径
				p.assign(fileinfo.name);
				if(p!="build.exe")files.push_back(p);  //这一行可以给出文件名
			}
		} while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
