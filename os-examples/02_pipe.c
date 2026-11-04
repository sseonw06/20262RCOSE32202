// pipe()로 부모 -> 자식 방향으로 문자열을 보내는 예제
// 컴파일: gcc 02_pipe.c -o pipe
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];  // fd[0]: 읽기 끝, fd[1]: 쓰기 끝
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);  // 자식은 읽기만 한다
        char buf[128];
        ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("[child] received: %s\n", buf);
        }
        close(fd[0]);
        return 0;
    }

    close(fd[0]);  // 부모는 쓰기만 한다
    const char *msg = "hello from parent";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);  // 다 쓰면 닫아야 자식이 EOF를 받을 수 있다
    wait(NULL);
    return 0;
}
