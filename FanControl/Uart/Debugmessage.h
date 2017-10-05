#ifndef __LOGFILE__
#define __LOGFILE__


#include <stdarg.h>

/*! \enum verbositylevels
	debug - used for debug messages - and testing
	info - used for information messages non failure
	important - usesd for non failure important messages 
	warning - used for messages which can cause to failure
	critical - used for messages before the failure 
	fatal - used for messages on failure, after that system must shutdown
*/



enum verbositylevels {
    vrlvl_debug =0x01,
    vrlvl_info,
    vrlvl_important,
    vrlvl_warning,
    vrlvl_critical,
    vrlvl_fatal
};


/*! \fn void setVerbosityLevel(int lvl)
    \brief set verbositylevel
    \param lvl - see enum for verbositylevels
*/
void setVerbosityLevel(int lvl);


/*! \fn void INFOMESSAGE(char* format,...)
    \brief prints a function for INFO verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void INFOMESSAGE(char* format,...);

/*! \fn void DEBUGMESSAGE(char* format,...)
    \brief prints a function for DEBUG verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void DEBUGMESSAGE(char* format,...);

/*! \fn void IMPORTANTMESSAGE(char* format,...)
    \brief prints a function for IMPORTANT verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void IMPORTANTMESSAGE(char* format,...);

/*! \fn void WARNING(char* format,...)
    \brief prints a function for WARNING verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void WARNING(char* format,...);

/*! \fn void CRITICALMESSAGE(char* format,...)
    \brief prints a function for CRITICAL verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void CRITICALMESSAGE(char* format,...);

/*! \fn void FATALMESSAGE(char* format,...)
    \brief prints a function for FATAL verbositylevel
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void FATALMESSAGE(char* format,...);

/*! \fn void INFOMESSAGE(char* format,...)
    \brief prints a function for variable verbositylevel
    \param lvl - verbosity level
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void writeverbositylog(int, char* format,va_list );

/*! \fn void writelog(char* format,...)
    \brief non verbosity printing and logging function
    \param *format pointer on the data string
    \param ... varable length of arguments - see <stdarg.h>
*/
void writelog(char* format,...);

void setOutputhandler(int (*input)(unsigned char c));

#endif
