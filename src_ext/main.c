#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
#include <errno.h>

#include "myxml.h"

#define BUFFSIZE 10240
void usage(char* app)
{
	printf("%s xml filename.\n",app);
	exit(0);
}
int main(int argc,char* argv[])
{
	if(argc<2)
		usage(argv[0]);
	char buff[BUFFSIZE]={};

	/*
	 * read xml file to buff
	 */
	FILE* pfile=fopen(argv[1],"r");
	if(pfile==NULL){
		printf("open %s fail,%s\n",argv[1],strerror(errno));
		return -1;
	}
	int i=0;
	while(0x20130627)
	{
		char c=fgetc(pfile);
		if(c==EOF)
			break;
		else
			buff[i++]=c;
	}
	fclose(pfile);
	
	/*
	 * print all node
	 */
	myxml_node_struct* xml_root=myxml_parser_char(buff);
	if(!xml_root)
	{
		printf("sorry parse fail.\n");
		return -1;
	}
	i=0;
	myxml_node_struct* xml_node=xml_root->child_node;
	while(xml_node) //manufacturer list 
	{
		printf("node%d:%s ",i++,xml_node->name);
		myxml_attribute_struct *attr_man=xml_node->attribute;
		while(attr_man) //manufacturer attribute  list 
		{
			printf("%s:%s ",attr_man->name,attr_man->value);
			attr_man = attr_man->next;
		}
		printf("\n");
		myxml_node_struct* mode=xml_node->child_node;
		while(mode) //model list 
		{
			printf("\t");
			printf("%s ",mode->name);
			myxml_attribute_struct *attr_mode=mode->attribute;
			while(attr_mode) //model attribute list
			{
				printf("%s:%s ",attr_mode->name,attr_mode->value);
				attr_mode = attr_mode->next;
			}
			printf("\n");
			myxml_node_struct* arg=mode->child_node;
			while(arg)//arg list
			{
				printf("\t\t");
				printf("%s\t:%s\n",arg->name,arg->content);
				arg=arg->next_node;
			}
			mode = mode->next_node;
			
		}
		
		printf("\n");
		xml_node=xml_node->next_node;
	}

	/*
	*UI: offer query service
	*/
	while(1)
	{
		myxml_node_struct* man_head=xml_root->child_node;//manufacturer list head
		int getresult=0;
		printf("############# input your projector's manufacturer and model ##########\n");
		printf("eg.\t:epson 520\n:");
		char man[10]={},model[10]={};
		scanf("%s %s",&man,&model);
		printf("your input\t:manufacturer is \"%s\",model is\"%s\"\n\n",man,model);
		while(man_head)
		{
			myxml_attribute_struct * man_value = man_head->attribute;
			if(!strcmp(man_value->value,man))//manufacturer matched 
			{	
				printf("manufacturer matched.\n");
				myxml_node_struct* model_head = man_head->child_node;
				while(model_head)
				{
					myxml_attribute_struct *model_value = model_head->attribute;
					if(strstr(model_value->value,model))//model matched
					{
						printf("model matched too,here is the result:\n");
						myxml_node_struct* result=model_head->child_node;
						while(result)//show result
						{
							printf("%s\t:%s\n",result->name,result->content);
							result = result->next_node;
						}
						getresult=1;
						break;
					}
					else
						model_head = model_head->next_node;
				}
			}
			else
				man_head = man_head->next_node;
			if(getresult)
				break;
		}
		if(!getresult)
			printf("sorry,not found\n");
	}
}
