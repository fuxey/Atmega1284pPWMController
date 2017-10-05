#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "Debugmessage.h"


static int (* out_handler)(unsigned char c) = NULL;
int level=0;

/*! \fn void setVerbosityLevel(int lvl)
    \brief set verbositylevel
    \param lvl - see enum for verbositylevels
*/
void setVerbosityLevel(int lvl){
    level = lvl;
}
/*! \fn void INFOMESSAGE(char* format,...)
    \brief prints a function for INFO verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void INFOMESSAGE(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_info,format,ap);
}
/*! \fn void DEBUGMESSAGE(char* format,...)
    \brief prints a function for DEBUG verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void DEBUGMESSAGE(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_debug,format,ap);
}
/*! \fn void IMPORTANTMESSAGE(char* format,...)
    \brief prints a function for IMPORTANT verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/

void IMPORTANTMESSAGE(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_important,format,ap);
}

/*! \fn void WARNING(char* format,...)
    \brief prints a function for WARNING verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void WARNING(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_warning,format,ap);
}

/*! \fn void CRITICALMESSAGE(char* format,...)
    \brief prints a function for CRITICAL verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void CRITICALMESSAGE(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_critical,format,ap);
}

/*! \fn void FATALMESSAGE(char* format,...)
    \brief prints a function for FATAL verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void FATALMESSAGE(char* format,...){
    va_list ap;
    va_start(ap, format);
    writeverbositylog(vrlvl_fatal,format,ap);
}


/*! \fn void writeverbositylog(int lvl,char* format,...)
    \brief prints a function for variable verbositylevel
    \param lvl - verbosity level
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/


void writeverbositylog(int lvl, char* format,va_list ap){
	char prefix[14];
	char msg[100];
    char *ptr;
    ptr= &prefix;



    memset(prefix,0,14);

    /*if verbosity level is set higher than message -- do not print message*/
    if( level > lvl)
        return;

    switch(lvl){
        case vrlvl_debug : strcat(prefix,"[ DEBUG ]"); break;
        case vrlvl_info: strcat(prefix,"[ INFO ]"); break;
        case vrlvl_important: strcat(prefix,"[ IMPORTANT ]"); break;
        case vrlvl_warning: strcat(prefix,"[ WARNING ]"); break;
        case vrlvl_critical: strcat(prefix,"[ CRTITICAL ]"); break;
        case vrlvl_fatal: strcat(prefix,"[ FATAL ]"); break;
        default : strcat(prefix,"[ DEBUG ]"); break;
    }


    memset(msg,0,100);


    vsprintf(msg,format,ap);
   // writelog(format,&ap);

    va_end(ap);
    while(*ptr){
    	out_handler(*ptr);
    	ptr++;
    }
    ptr = &msg;

    while(*ptr){
       	out_handler(*ptr);
       	ptr++;
    }

#if 0
    logfd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRGRP);
       if (logfd == -1) {
           writelog("Could not open log-file: %s \n", strerror(errno));
           exit(EXIT_FAILURE);
       }
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    char *time = asctime( localtime(&ltime));
    time[strlen(time) - 1] = 0;

    if(strstr(msg,"\n") != NULL){
        sprintf(logstr, "|%s| [ %s ] > %s",prefix, time, msg);
    }else {
        sprintf(logstr, "|%s| [ %s ] > %s\n",prefix, time, msg);
    }

    puts(logstr);
    num = write(logfd, (const char *)logstr, strlen((const char *)logstr));
    if (num == -1)
        perror("write error");

    close(logfd);
#endif
}

/*! \fn void writelog(char* format,...)
    \brief non verbosity printing and logging function
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
#if 0
void writelog(char* format,...) {

    int logfd=-1;
    va_list ap;
    char msg[1000];


    va_start(ap, format);


    memset(msg,0,1000);


    vsprintf(msg,format,ap);
   // writelog(format,&ap);

    va_end(ap);


    int num;


    logfd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRGRP);
       if (logfd == -1) {
           writelog("Could not open log-file: %s \n", strerror(errno));
           exit(EXIT_FAILURE);
       }
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    char *time = asctime( localtime(&ltime));
    time[strlen(time) - 1] = 0;

    if(strstr(msg,"\n") != NULL){
        sprintf(logstr, "[ %s ] > %s", time, msg);
    }else {
        sprintf(logstr, "[ %s ] > %s\n", time, msg);
    }

    puts(logstr);
    num = write(logfd, (const char *)logstr, strlen((const char *)logstr));
    if (num == -1)
        perror("write error");

    close(logfd);


}
#endif

void setOutputhandler(int (*input)(unsigned char c)){
	out_handler = input;
}


