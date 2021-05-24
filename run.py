from subprocess import run,PIPE,CalledProcessError
import sys




cnt = 0
score_sum = 0

for i in range(100):
    input_file = "in/{:0>4}.txt".format(i)
    command_draw = ["cargo","run","--release","--bin","tester", input_file, "./a.out"]
    with open("tmp.txt", "w") as f:
        try:
            run(command_draw,check=True,stderr=f)
        except CalledProcessError:
            print('外部プログラムの実行に失敗しました [' + " ".join(command_draw) + ']', file=sys.stderr)
            sys.exit(1)
    
    with open("tmp.txt", "r") as f:
        *a, = f.read().split("Score = ")
        score_sum += int(a[-1])
        cnt += 1
print("average", score_sum/cnt)
