/*
 *  author  :   Gu-hwan Bae
 *  date    :   May 28, 2018
 */

 /* Logging user level log. 
    This program open an non-existent file. */

#include <syslog.h> /* system logging facilities */
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fp;
    
    const char* meaning_less = "Lisa Simpson is the smartest of the Simpsons.";
    fp = fopen(meaning_less, "r");

    if(!fp) {
        /* 파일 열기에 실패함. */
        syslog(LOG_ERR | LOG_USER, "Failed to open %s. - %m\n", meaning_less);
    }

    return 0;
}
