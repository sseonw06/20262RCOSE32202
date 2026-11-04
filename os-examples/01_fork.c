// fork()로 자식 프로세스를 만들고, 부모가 자식의 종료를 기다리는 예제
// 컴파일: gcc 01_fork.c -o fork
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int x = 10;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // 자식은 부모의 메모리를 복사해서 받기 때문에 x를 바꿔도 부모에는 영향이 없다
        x += 5;
        printf("[child]  pid=%d, ppid=%d, x=%d\n", getpid(), getppid(), x);
        exit(7);
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        printf("[parent] child %d exited with code %d\n", pid, WEXITSTATUS(status));
    printf("[parent] pid=%d, x=%d\n", getpid(), x);
    return 0;
}
