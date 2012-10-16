/******************************************************************************
 * Project         Persistency
 * (c) copyright   2012
 * Company         XS Embedded GmbH
 *****************************************************************************/
/******************************************************************************
   Permission is hereby granted, free of charge, to any person obtaining 
   a copy of this software and associated documentation files (the "Software"), 
   to deal in the Software without restriction, including without limitation 
   the rights to use, copy, modify, merge, publish, distribute, sublicense, 
   and/or sell copies of the Software, and to permit persons to whom the 
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included 
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
   OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/
 /**
 * @file           persistence_client_library_test.c
 * @ingroup        Persistence client library test
 * @author         Ingo Huerner
 * @brief          Test of persistence client library
 * @see            
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>     /* exit */
#include <check.h>
#include <time.h>

#include "../include/persistence_client_library_key.h"
#include "../include/persistence_client_library_file.h"


#define BUF_SIZE     64
#define NUM_OF_FILES 3
#define READ_SIZE    1024

char* dayOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };



START_TEST (test_persGetData)
{
   int ret = 0;
   unsigned char* buffer = NULL;
   char sysTimeBuffer[256];
   buffer = malloc(READ_SIZE);

   struct tm *locTime;
   time_t t = time(0);
  
   locTime = localtime(&t);

   snprintf(sysTimeBuffer, 256, "\"%s %d.%d.%d - %d:%.2d:%.2d Uhr\"", dayOfWeek[locTime->tm_wday], locTime->tm_mday, locTime->tm_mon, (locTime->tm_year+1900),
                                                                  locTime->tm_hour, locTime->tm_min, locTime->tm_sec);
   printf("\n\n");

   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0xFF, "/language/country_code",         0, 0, buffer, READ_SIZE);   // "/Data/mnt-c/Appl-1/cached.gvdb"             => "/Node/pos/last position"
   printf("T E S T  Data - country_code: %s | size: %d \n", buffer, ret);
   fail_unless(strncmp((char*)buffer, "Custom plugin -> plugin_get_data_handle", strlen((char*)buffer)) == 0, "Buffer not correctly read");

   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0xFF, "/pos/last_position",         0, 0, buffer, READ_SIZE);   // "/Data/mnt-c/Appl-1/cached.gvdb"             => "/Node/pos/last position"
   fail_unless(strncmp((char*)buffer, "+48° 10' 38.95\", +8° 44' 39.06\"", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data - last_position: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0,    "/language/current_language", 3, 0, buffer, READ_SIZE);   // "/Data/mnt-wt/Shared/Public/wt.dconf"        => "/User/3/language/current_language"
   fail_unless(strncmp((char*)buffer, "S H A R E D   D A T A  => not implemented yet", strlen((char*)buffer)) == 0, "Buffer not correctly read");
   printf("T E S T  Data - current_language: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0xFF, "/status/open_document",      3, 2, buffer, READ_SIZE);   // "/Data/mnt-c/Appl-1/cached.gvdb"             => "/User/3/Seat/2/status/open_document"
   printf("T E S T  Data - last link: %s \n", buffer);
   fail_unless(strncmp((char*)buffer, "/var/opt/user_manual_climateControl.pdf", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data - open_document: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0x20, "/address/home_address",      4, 0, buffer, READ_SIZE);   // "/Data/mnt-c/Shared/Group/20/cached.dconf"   => "/User/4/address/home_address"
   fail_unless(strncmp((char*)buffer, "S H A R E D   D A T A  => not implemented yet", strlen((char*)buffer)) == 0, "Buffer not correctly read");
   printf("T E S T  Data - home_address: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0xFF, "/pos/last satellites",       0, 0, buffer, READ_SIZE);   // "/Data/mnt-wt/Appl-1/wt.gvdb"                => "/Node/pos/last satellites"
   fail_unless(strncmp((char*)buffer, "17", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data - last satellites: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0x84, "/links/last link",           2, 0, buffer, READ_SIZE);   // "/Data/mnt-wt/Appl-2/wt.gvdb"                => "/84/User/2/links/last link"
   fail_unless(strncmp((char*)buffer, "/last_exit/brooklyn", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data - last link: %s \n", buffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0x84, "/links/last link",           2, 1, buffer, READ_SIZE);   // "/Data/mnt-wt/Appl-2/wt.gvdb"                => "/84/User/2/links/last link"
   fail_unless(strncmp((char*)buffer, "/last_exit/queens", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data - last link: %s \n", buffer);
   printf("----------------------------------------------->\n\n");

   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   //ret = key_write_data(0xFF, "/status/open_document",          1, 2, (unsigned char*)sysTimeBuffer, READ_SIZE);   // "/Data/mnt-c/Appl-1/cached.gvdb"             => "/User/3/Seat/2/status/open_document"
   printf("T E S T  write data /status/open_document: %s \n", sysTimeBuffer);
   printf("----------------------------------------------->\n\n");


   printf("<-----------------------------------------------\n");
   memset(buffer, 0, READ_SIZE);
   ret = key_read_data(0xFF, "/status/open_document",           1, 2, buffer, READ_SIZE);   // "/Data/mnt-c/Appl-1/cached.gvdb"             => "/User/3/Seat/2/status/open_document"
   printf("T E S T  Data /status/open_document: %s \n", buffer);
   fail_unless(strncmp((char*)buffer, "empty", strlen(sysTimeBuffer)) == 0, "Buffer not correctly read");

   printf("----------------------------------------------->\n\n");


   free(buffer);
}
END_TEST



START_TEST (test_persGetDataHandle)
{
   int ret = 0, handlePos = 0, handleLang = 0, handleStatus = 0, handleHome = 0;
   unsigned char* buffer = NULL;
   char sysTimeBuffer[128];
   buffer = malloc(READ_SIZE);

   struct tm *locTime;
   time_t t = time(0);
  
   locTime = localtime(&t);

   snprintf(sysTimeBuffer, 128, "\"%s %d.%d.%d - %d:%.2d:%.2d Uhr\"", dayOfWeek[locTime->tm_wday], locTime->tm_mday, locTime->tm_mon, (locTime->tm_year+1900), 
                                                                  locTime->tm_hour, locTime->tm_min, locTime->tm_sec);
   printf("\n\n");

   memset(buffer, 0, READ_SIZE);
   handlePos = key_handle_open(0xFF, "/posHandle/last_position", 0, 0);
   ret = key_handle_read_data(handlePos, buffer, READ_SIZE);
   fail_unless(strncmp((char*)buffer, "", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  handle: %d | Data: %s \n\n", handlePos, buffer);

   memset(buffer, 0, READ_SIZE);
   handleLang = key_handle_open(0, "/languageHandle/current_language", 3, 0);
   ret = key_handle_read_data(handleLang, buffer, READ_SIZE);
   printf("T E S T  handle: %d | Data: %s \n\n", handleLang, buffer);

   memset(buffer, 0, READ_SIZE);
   handleStatus = key_handle_open(0xFF, "/statusHandle/open_documen", 3, 2);
   ret = key_handle_read_data(handleStatus, buffer, READ_SIZE);
   printf("T E S T  handle: %d | Data: %s \n\n", handleStatus, buffer);

   // close handle
   key_handle_close(handleLang);

   memset(buffer, 0, READ_SIZE);
   handleHome = key_handle_open(0x20, "/address/home_address", 4, 0);
   ret = key_handle_read_data(handleHome, buffer, READ_SIZE);
   printf("T E S T  handle: %d | Data: %s \n\n", handleHome, buffer);

   free(buffer);
}
END_TEST



START_TEST(test_persSetData)
{
   unsigned char* buffer = NULL;
   buffer = malloc(READ_SIZE);                            
   memset(buffer, 0, READ_SIZE);


   free(buffer);
}
END_TEST



START_TEST(test_persSetSharedData)
{
   int ret = 0;
   unsigned char* buffer = NULL;
   buffer = malloc(READ_SIZE);                            


   memset(buffer, 0, READ_SIZE);
   ret = key_write_data(0x20, "/address/home_address",      4, 0, buffer, READ_SIZE);
   fail_unless(strncmp((char*)buffer, "", ret-1) == 0, "Buffer not correctly read");
   printf("T E S T  Data: %s \n\n", buffer);

   free(buffer);
}
END_TEST



START_TEST(test_persGetData_file)
{
   int ret = 0;
   unsigned char* buffer = NULL;
   buffer = malloc(READ_SIZE);


   memset(buffer, 0, READ_SIZE);

   ret = file_open(0xFF, "/media/mediaDB.db", 1, 1);
   fail_unless(ret != -1, "Could not open file");
   printf("T E S T  Data: %s \n\n", buffer);

   free(buffer);
}
END_TEST




static Suite * persistencyClientLib_suite()
{
   Suite * s  = suite_create("Persistency client library");

   TCase * tc_persGetData = tcase_create("persGetData");
   tcase_add_test(tc_persGetData, test_persGetData);

   TCase * tc_persGetDataHandle = tcase_create("persGetDataHandle");
   tcase_add_test(tc_persGetDataHandle, test_persGetDataHandle);

   TCase * tc_persSetData = tcase_create("persSetData");
   tcase_add_test(tc_persSetData, test_persSetData);

   TCase * tc_persSetSharedData = tcase_create("persSetSharedData");
   tcase_add_test(tc_persSetSharedData, test_persSetSharedData);

   TCase * tc_persGetData_file = tcase_create("persGetData_file");
   tcase_add_test(tc_persGetData_file, test_persGetData_file);

   suite_add_tcase(s, tc_persGetData);
   /*suite_add_tcase(s, tc_persGetDataHandle);
   suite_add_tcase(s, tc_persSetData);
   suite_add_tcase(s, tc_persSetSharedData);
   suite_add_tcase(s, tc_persGetData_file);
*/
   return s;
}




int main(int argc, char *argv[])
{
   int nr_failed;

   Suite * s = persistencyClientLib_suite();
   SRunner * sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   nr_failed = srunner_ntests_failed(sr);
   srunner_free(sr);

   return (0==nr_failed)?EXIT_SUCCESS:EXIT_FAILURE;

}
