from subprocess import run,PIPE,CalledProcessError,Popen
import sys

cnt = 0
score_sum = 0


loop_num = 100
max_process = 8
proc_list = []

for i in range(loop_num):
    print(i)
    input_file = "in/{:0>4}.txt".format(i)
    command_draw = ["cargo","run","--release","--bin","tester", input_file, "./a.out"]
    with open("out","w") as for_stdout:
        with open("tmp/tmp{:0>4}.txt".format(i), "w") as f:
            proc = Popen(command_draw,stderr=f,stdout=for_stdout)
            proc_list.append(proc)
    if (i+1)%max_process == 0 or i+1 == loop_num:
        for subproc in proc_list:
            subproc.wait()
        proc_list = []


for i in range(loop_num):
    with open("tmp/tmp{:0>4}.txt".format(i), "r") as f:
        *a, = f.read().split("Score = ")
        score_sum += int(a[-1])
        cnt += 1
        print(a[-1])

print("average", score_sum/cnt)
