#题目: 用两个栈来实现一个队列，完成队列的Push和Pop操作
（1）程序可以输入指令，字符串"PUSH","POP",注意不能接受其他字符串
（2）栈和队列最大长度为5，长度为5之后，在输入要提示stack已经满了
（3）输入输出PUSH和POP指令时，打印当前队列的内容

#例子1
COMMAND:PUSH,POP,EXIT,Please input one command!
PUSH
1
queue[0]=1
PUSH
2
queue[0]=2
queue[1]=1
POP
queue[0]=2


//////////////////////////
#编译和运行指令:
a. compiling command: gcc stackqueue.c
b. running command: ./a.out
//////////////////////
