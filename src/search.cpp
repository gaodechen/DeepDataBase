/*
// ----------------------------------------------------------------------
 // File    : BPtree.h
 // Author  : Mandeep singh
 // Purpose : searching of table contents
 //			  based on primary key or other attributes
 //
 //
 // DeepDataBase, Copyright (C) 2015 - 2017
 //
 // This program is free software; you can redistribute it and/or
 // modify it under the terms of the GNU General Public License as
 // published by the Free Software Foundation; either version 2 of the
 // License, or (at your option) any later version.
 //
 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 // General Public License for more details.
 //
 // You should have received a copy of the GNU General Public License along
 // with this program; if not, write to the Free Software Foundation, Inc.,
 // 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

// ----------------------------------------------------------------------
*/

#include "search.h"
#include "file_handler.h"
#include "BPtree.h"

void search(){
	//search for particular table or any specific entry inside table
	cout<<"1.search table\n2.search particular entry in table\n\n";
	int ch;
	cin>>ch;
	char *tab;
	tab=(char*)malloc(sizeof(char)*MAX_NAME);
	if(ch==1){
		cout<<"enter table name: ";
		cin>>tab;
		//check if table exists
		int check=search_table(tab);
		if(check==1) printf("\n%s exists!!!\n",tab);
		else printf("\n%s doesn't exist in table entry\n\n",tab);
	}
	else if(ch==2){
		cout<<"enter table name: ";
		cin>>tab;
		int check=search_table(tab);
		if(check==1){
			printf("%s exists!!!\n\nEnter key to search\n\n",tab);
			//open %s meta data file and display column details;
			table inp1;
			FILE *fp = open_file(tab, const_cast<char*>("r"));
     		 int i=0;
			while(fread(&inp1,sizeof(table),1,fp)){
				for(i=0;i<inp1.count;i++){
					cout<<inp1.col[i].col_name<<"("<<inp1.col[i].type<<"),size:"<<inp1.col[i].size;
					cout<<"\t";
				}
			}
			int pri_int;
			int c;
			char d[MAX_NAME];
			char pri_char[MAX_NAME];
			BPtree mytree(tab);
			int ret=0;
			if(inp1.col[0].type==INT){
				cout<<"\nenter key[col 0] to search\n";
				cin>>pri_int;
				 ret = mytree.get_record(pri_int);
				 if (ret == BPTREE_SEARCH_NOT_FOUND){
				 	printf("\nSearching (%d) -> NOT FOUND !!", pri_int);
				 }
				 else{
				 	 //printf("\nSearch (%d) exists -> record num = %d", pri_int, ret);
				 	 printf("\n %d exists \n\n",pri_int);
				 	 //print the details of the particular row;
				 	FILE *fpz;
				 	char *str1;
					printf("\n------------------------------------\n");
				 	str1=(char*)malloc(sizeof(char)*MAX_PATH);
				 	sprintf(str1,"table/%s/file%d.dat",tab,ret);
				 	fpz=fopen(str1,"r");

				 	for(int j=0;j<inp1.count;j++){
				 		if(inp1.col[j].type==INT){
				 			fread(&c,1,sizeof(int),fpz);
				 			cout<<c<<"\t";
						}
				 		else if(inp1.col[j].type==VARCHAR){
				 			fread(d,1,sizeof(char)*MAX_NAME,fpz);
				 			cout<<d<<"\t";
				 		}
				 	}
					printf("\n------------------------------------\n");
				 	fclose(fpz);
				 	free(str1);

				 }
			}
			else if(inp1.col[0].type==VARCHAR){
				cout<<"\nenter  key[col 0] to search\n";
				cin>>pri_char;
				void *arr[MAX_NAME];
				arr[0]=(char*)malloc(sizeof(char)*MAX_NAME);
				arr[0]=pri_char;
				ret=mytree.get_record(*(int*)arr[0]);
				if (ret == BPTREE_SEARCH_NOT_FOUND){
					printf("\nSearching (%s) -> NOT FOUND !!", pri_char);
				}
			    else{
				   // printf("\nSearching (%s) -> record num = %d", pri_char, ret);
				    printf("\n%s exists\n\n",pri_char);

				    //print the details of the particular row;
				   	FILE *fpz;
				   	char *str1;
				   	str1=(char*)malloc(sizeof(char)*MAX_PATH);
				   	sprintf(str1,"table/%s/file%d.dat",tab,ret);
				   	fpz=fopen(str1,"r");
				   	printf("\n------------------------------------\n");
				 	for(int j=0;j<inp1.count;j++){
				   		if(inp1.col[j].type==INT){
				   			fread(&c,1,sizeof(int),fpz);
				   			cout<<c<<"\t";
				   		}
				   		else if(inp1.col[j].type==VARCHAR){
				   			fread(d,1,sizeof(char)*MAX_NAME,fpz);
				   			cout<<d<<"\t";
				   		}
				   	}
				 	printf("\n-------------------------------------\n");
				   	fclose(fpz);
				   	free(str1);
			    }

			}

		}
		else{
			printf("%s doesn't exists!!!\n\n",tab);
		}
	}
	else{
		cout<<"wrong input!!!\n\n";
		return;
	}
	free(tab);
}
