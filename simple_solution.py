query_num = 1000
for _ in range(query_num):
    si_k, sj_k, ti_k, tj_k = map(int, input().split())

    ans = ""

    #縦に動く
    if si_k < ti_k: #下
        ans += "D" * (ti_k - si_k)
    else: #上
        ans += "U" * (si_k - ti_k)

    #横に動く
    if sj_k < tj_k: #右
        ans += "R" * (tj_k - sj_k)
    else: #左
        ans += "L" * (sj_k - tj_k)
    
    print(ans)
    path_length = input() #出力したパスの長さ * ノイズ




