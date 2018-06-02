#!/bin/bash

# Shell command와 pipe(|)를 이용해서 System information을 파일에 기록한다.

# first_command | second_command

# first_command는 uname -a 이다.
# uname -a는 System info를 standard output(console monitor)로 출력한다.

# pipe(|)는 first_command의 standard output을
# second_command의 standard input으로 변경한다.

# second_command는 grep이다.
# grep은 standard input을 읽어서 linux 혹은 Linux 문자열을 찾은 후 일치하면,
# 결과값을 sysinfo_from_sh(Text file)로 Redirection한다.

uname -a | grep [Ll]inux > sysinfo_from_sh
