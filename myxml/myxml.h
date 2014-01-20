/*        Filename: myxml.h
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

#ifndef MYXML_H_2008_5_20
#define MYXML_H_2008_5_20

#ifndef MYSRC_WITHOUT_XML

#include "myxml_struct.h"

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

//the xml parser only support GB2312 and UTF-8

	
//not parser note or head
extern myxml_node_struct* myxml_parser_char(const char *param_char);
//parser note and head
extern myxml_node_struct* myxml_parser_char2(const char *param_char);
extern void myxml_free(myxml_node_struct*param_node);


extern myxml_head_struct* myxml_parser_head_char(const char *param_char);
extern void myxml_head_free(myxml_head_struct*param);

extern myxml_head_struct* myxml_head_create(const char *param_version,const myxml_encoding_enum param_encoding);
extern int myxml_head_set_version(myxml_head_struct*param_head,const char*param_version);
extern int myxml_head_set_encoding(myxml_head_struct*param_head,const myxml_encoding_enum param_encoding);
extern int myxml_head_to_char(myxml_head_struct*param_head,char* param_string,const int param_string_len);

extern myxml_node_struct* myxml_create_node(const char*param_name,const char*param_content);
extern myxml_node_struct* myxml_create_note(const char*param_note);
extern myxml_node_struct* myxml_create_head(const char*param_version,const char*param_encoding);
extern int myxml_set_content(myxml_node_struct*param_node,const char *param_content);
extern int myxml_add_attribute(myxml_node_struct*param_node,const char*param_name,const char*param_value);
extern int myxml_add_child_node(myxml_node_struct*param_father_node,myxml_node_struct*param_child_node);
extern int myxml_add_pre_node(myxml_node_struct*param_node,myxml_node_struct*param_new_node);
extern int myxml_add_next_node(myxml_node_struct*param_node,myxml_node_struct*param_new_node);
extern int myxml_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len);
extern int myxml_set_note(myxml_node_struct*param_node,const char* param_note);
extern myxml_node_struct *myxml_unlink_node(myxml_node_struct*param_unlink_node);

extern int myxml_all_to_char(myxml_head_struct*param_head,myxml_node_struct *param_node,char *param_string,const int param_string_len);
//with tab
extern int myxml_to_char2(myxml_node_struct *param_node,char *param_string,const int param_string_len);

//extern void test();

#ifdef __cplusplus
}
#endif//__cplusplus

#endif//MYSRC_WITHOUT_XML
#endif /*MYXML_H_*/
