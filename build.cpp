#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<vector>
#include<windows.h>
#include<io.h>
using namespace std;
#define MAX_PATHH 80
string ad;
void getFiles( string path, string path2, vector<string>& files );
int main() {
	
	cin>>ad;
	
	vector<string> files;
	char   buffer[MAX_PATHH];
	getcwd(buffer, MAX_PATHH);
	string filePath;
	filePath.assign(buffer).append("\\");
	filePath+=ad;
	filePath+="\\";
	ad+=".html";
	getFiles(filePath,"", files );
	int size = files.size();
	filePath+=ad;
	freopen(filePath.c_str(),"w",stdout);
	printf("<!DOCTYPE html>\n");
	printf("<html style=\"width:100%;\">\n");
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
	long   hFile   =   0;
	struct _finddata_t fileinfo;
	string p,p2;
	if((hFile = _findfirst(p.assign(path).append(path2).append("*").c_str(),&fileinfo)) !=  -1) {
		do {
			if((fileinfo.attrib &  _A_SUBDIR)) {
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\"),p2.assign(fileinfo.name).append("\\"), files );
			}
			else if(strcmp(ad.c_str(),fileinfo.name)!=0)files.push_back(p.assign(path2).append(fileinfo.name) );
				//files.push_back(p.assign(fileinfo.name) ); 
		} while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
