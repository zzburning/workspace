/*        Filename: myxml_struct.h
 **********************************************************
 * Description:
 *        this is myxml.h header.
 * Version:
 *        V_0.1 2008.5.20
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.5.20 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */


#ifndef MYXML_STRUCT_H_2008_5_20
#define MYXML_STRUCT_H_2008_5_20

#ifndef MYSRC_WITHOUT_XML

typedef struct _myxml_attribute_struct
{
	char *name;
	char *value;
	struct _myxml_attribute_struct *pre;
	struct _myxml_attribute_struct *next;
}myxml_attribute_struct;

typedef enum _myxml_node_type
{
	myxml_node_error,
	myxml_node_node,
	myxml_node_note,
	myxml_node_head,
	myxml_node_null,//only use in file myxml.c
}myxml_node_type;

typedef struct _myxml_node_struct
{
	myxml_node_type type;////////////////////node note head
	int depth;///////////////////////////////node note head
	char *name;//////////////////////////////node
	char *content;///////////////////////////node note
	myxml_attribute_struct *attribute;///////node      head
	struct _myxml_node_struct *father_node;//node note
	struct _myxml_node_struct *child_node;///node
	struct _myxml_node_struct *next_node;////node note head
	struct _myxml_node_struct *pre_node;/////node note
	
}myxml_node_struct;

typedef enum _myxml_encoding_enum
{
	myxml_encode_unknow,
	myxml_encode_gb2312,
	myxml_encode_utf8,
}myxml_encoding_enum;

typedef struct _myxml_head_struct
{
	char *version;
	myxml_encoding_enum encoding;
}myxml_head_struct;

#endif//MYSRC_WITHOUT_XML
#endif /*MYXML_STRUCT_H_*/
