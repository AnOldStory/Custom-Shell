#include <stdio.h>
#include <unistd.h>    // getlogin
#include <pwd.h>       // getpwnam
#include <sys/types.h> // uid_t

int main()
{
    char *user_name;
    struct passwd *user_pw;

    user_name = getlogin();        // 로그인 이름 구하기
    user_pw = getpwnam(user_name); // 로그인 이름으로  사용자 정보 구하기

    printf("user name      :%s\n", user_pw->pw_name);
    printf("user id        :%d\n", user_pw->pw_uid);
    printf("group id       :%d\n", user_pw->pw_gid);
    printf("reall name     :%s\n", user_pw->pw_gecos);
    printf("home directory :%s\n", user_pw->pw_dir);
    printf("shell program  :%s\n", user_pw->pw_shell);
    return 0;
}