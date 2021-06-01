query_num = 1000
for _ in range(query_num):
    si_k, sj_k, ti_k, tj_k = map(int, input().split())

    ans = ""
    while(si_k!=ti_k or sj_k!=tj_k):
        #縦に動く
        if si_k < ti_k: #下
            ans += "D" 
            si_k+=1
        elif si_k > ti_k: #上
            ans += "U" 
            si_k-=1

        #横に動く
        if sj_k < tj_k: #右
            ans += "R" 
            sj_k+=1

        elif sj_k > tj_k: #左
            ans += "L" 
            sj_k-=1

    
    print(ans)
    path_length = input() #出力したパスの長さ * ノイズ