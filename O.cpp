/*
　　　∫ ∫ ∫
　　　ノヽ
　　（＿　 ）
　（＿　　　 ）
（＿＿＿＿＿＿ ）
　ヽ(´･ω･)ﾉ　
　　 |　 /
　　 UU
*/
#pragma region macro
#include <bits/stdc++.h>
typedef long long int64;
using namespace std;
typedef vector<int> vi;
const int MOD = (int)1e9 + 7;
const int64 INF = 1LL << 62;
const int inf = 1<<30;
const char bn = '\n';
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i,s,n) for (int i = s; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
#define mp make_pair
template <typename T>
ostream& operator<<(ostream& os, const vector<T> &V){
    int N = V.size();
    REP(i,N){
        os << V[i];
        if (i!=N-1) os << " ";
    }
    os << "\n";
    return os;
}
template <typename T,typename S>
ostream& operator<<(ostream& os, pair<T,S> const&P){
    os << "(";
    os << P.first;
    os << " , ";
    os << P.second;
    os << ")";
    return os;
}
template <typename T,typename S,typename U>
ostream& operator<<(ostream& os, tuple<T,S,U> const& P){
    os << "(";
    os << get<0>(P);
    os << ", ";
    os << get<1>(P);
    os << ", ";
    os << get<2>(P);
    os << ")";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, set<T> &S){
    auto it=S.begin();
    while(it!=S.end()){
        os << *it;
        os << " ";
        it++;
    }
    os << "\n";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, deque<T> &q){
    for(auto it=q.begin();it<q.end();it++){
        os<<*it;
        os<<" ";
    }
    os<<endl;
    return os;
}
template <typename T,typename S>
ostream& operator<<(ostream& os, map<T,S> const&M){
    for(auto e:M){
        os<<e;
    }
    os<<endl;
    return os;
}
vector<pair<int,int>> dxdy = {mp(0,1),mp(1,0),mp(-1,0),mp(0,-1)};
#pragma endregion
//fixed<<setprecision(10)<<ans<<endl;

const int N = 30;
const int node_num = N*N;
int encode(int h, int w){
    return h*N + w;
}

int encode(pair<int,int> position){
    int h,w; tie(h,w) = position;
    return encode(h,w);
}

pair<int,int> decode(int node){
    return make_pair(node/N, node%N);
}

bool is_inside(int h,int w){
    return (0<=h && h<N && 0<=w && w<N);
}

bool is_inside(pair<int,int> position){
    return is_inside(position.first, position.second);
}



vector<int> dijkstra(vector<vector<pair<int,int64>>> const& edge, int source, int target){
    vector<int64> distances(node_num,INF);
    priority_queue<pair<int64,int>,vector<pair<int64,int>>, greater<pair<int64,int>> > que;
    que.push(mp(0, source));
    vector<bool> visited(node_num,false);
    vector<int> move_from(node_num, -1);
    
    int from,to;
    int64 dist,cost;
    while(!que.empty()){
        tie(dist,from) = que.top(); que.pop();
        if (visited[from]) continue;
        visited[from] = true;
        distances[from] = dist;
        for(auto e:edge[from]){
            tie(to,cost) = e;
            if (visited[to]) continue;
            if(chmin(distances[to], int64(dist+cost))){
                que.push(mp(dist+cost, to));
                move_from[to] = from;
            }
        }
    }
    // debug(distances[target])
    return move_from;
}

string encode_to_ans(int const& source, int const& target, vector<int> const& move_from){
    string ans = "";
    int now_position = target;
    
    while(now_position != source){
        int now_h,now_w,from_h,from_w;
        tie(now_h, now_w) = decode(now_position);
        tie(from_h, from_w) = decode(move_from[now_position]);
        int dh = now_h-from_h, dw = now_w-from_w;
        if(dh==0 && dw==1) ans += "R";
        else if(dh==0 && dw==-1) ans += "L";
        else if(dh==1 && dw==0) ans += "D";
        else if(dh==-1 && dw==0) ans += "U";
        else assert(false);
        now_position = move_from[now_position];
    }

    reverse(ALL(ans));

    return ans;
}

int get_info_cnt(int h1, int w1, int h2, int w2, vector<vector<pair<int,int64>>> const& estimated_edge){
    int cnt = 0;
    if(h1==h2){
        int h = h1;
        for(int w=min(w1,w2); w<=max(w1,w2); w++){
            // debug(estimated_edge[encode(h, w)][encode(h, w+1)].first)
            cnt += estimated_edge[encode(h, w)][encode(h, w+1)].first;
        }
    }else if(w1==w2){
        int w = w1;
        for(int h=min(h1,h2); h<=max(h1,h2); h++){
            // debug(estimated_edge[encode(h, w)][encode(h+1, w)].first)
            cnt += estimated_edge[encode(h, w)][encode(h+1, w)].first;
        }
    }else assert(false);
    return cnt;
}

string get_L_path(int const& source, int const& target, vector<vector<pair<int,int64>>> const& estimated_edge){
    string path = "";
    string LRUD = "LRUD";
    // debug(decode(source))
    // debug(decode(target))

    int s_h, s_w, t_h, t_w;
    tie(s_h, s_w) = decode(source); tie(t_h, t_w) = decode(target);

    int path1_info_cnt = get_info_cnt(s_h, s_w, s_h, t_w, estimated_edge) + get_info_cnt(s_h, t_w, t_h, t_w, estimated_edge); //左右行ってから上下
    int path2_info_cnt = get_info_cnt(s_h, s_w, t_h, s_w, estimated_edge) + get_info_cnt(t_h, s_w, t_h, t_w, estimated_edge); //上下行ってから左右

    // debug(mp(path1_info_cnt,path2_info_cnt))
    if(path1_info_cnt > path2_info_cnt){
        if(s_w < t_w){
            path += string(t_w-s_w, 'R');
        }else{
            path += string(s_w-t_w, 'L');
        }

        if(s_h < t_h){
            path += string(t_h-s_h, 'D');
        }else{
            path += string(s_h-t_h, 'U');
        }

    }else{
        if(s_h < t_h){
            path += string(t_h-s_h, 'D');
        }else{
            path += string(s_h-t_h, 'U');
        }

        if(s_w < t_w){
            path += string(t_w-s_w, 'R');
        }else{
            path += string(s_w-t_w, 'L');
        }
    }

    return path;
}

string solve(int const& source, int const& target, vector<vector<pair<int,int64>>> const& edge, int query, vector<vector<pair<int,int64>>> const& estimated_edge){
    string ans;
    const int first_servey = 100;
    if(query<first_servey){
        ans = get_L_path(source, target, estimated_edge);
    }else{
        auto move_from = dijkstra(edge, source, target);
        ans = encode_to_ans(source, target, move_from);
    }
    return ans;
}

pair<int,int64> add_pairs(pair<int,int64> const& A, pair<int,int64> const& B){
    return make_pair(A.first+B.first, A.second+B.second);
}

pair<int,int64> sub_pairs(pair<int,int64> const& A, pair<int,int64> const& B){
    return make_pair(A.first-B.first, A.second-B.second);
}

void add_edge_by_nears(int const& from_, int const& next_, pair<int,int64> info_nears, vector<vector<pair<int,int64>>>& edge, int init_cost){
    if(info_nears == mp(0,0LL)){
        edge[next_].emplace_back(from_, init_cost);
        edge[from_].emplace_back(next_, init_cost);
    }else{
        edge[next_].emplace_back(from_, info_nears.second / info_nears.first);
        edge[from_].emplace_back(next_, info_nears.second / info_nears.first);
    }
}


bool flag = false;
vector<vector<pair<int,int64>>> get_edge(vector<vector<pair<int,int64>>> const& estimated_edge){
    const int64 init_cost = 3000; //考慮するべき
    vector<vector<pair<int,int64>>> edge(node_num);

    const int cost_range = 8; //前後何個の情報で辺の重みを決定するか
    const int coef = 5; //自分の辺の情報の重み付け

    if(!flag){
        flag = true;
        cerr << "パラメータ\n";
        debug(cost_range)
        debug(init_cost)
        debug(coef)
    }

    //列
    REP(h,N){
        //累積和計算
        vector<pair<int,int64>> cumsum(N, mp(0,0));
        REP(w,N-1){
            pair<int,int> next_ = make_pair(h,w+1);
            cumsum[w+1] = add_pairs(cumsum[w], estimated_edge[encode(h,w)][encode(next_)]);
        }

        //前後K個ずつを使って辺重み計算
        REP(w,N-1){
            pair<int,int> next_ = make_pair(h,w+1);
            pair<int,int64> info_nears = sub_pairs(cumsum[min(N-1, w+cost_range)], cumsum[max(0, w-cost_range)]); //前後K個での和
            
            REP(_,coef){
                info_nears = add_pairs(info_nears, estimated_edge[encode(h,w)][encode(next_)]); //自分の辺の情報は重めに評価する
            }

            add_edge_by_nears(encode(h,w), encode(next_), info_nears, edge, init_cost);
        }   
    }

    //行
    REP(w,N){
        //累積和計算
        vector<pair<int,int64>> cumsum(N, mp(0,0));
        REP(h,N-1){
            pair<int,int> next_ = make_pair(h+1,w);
            cumsum[h+1] = add_pairs(cumsum[h], estimated_edge[encode(h,w)][encode(next_)]);
        }

        //前後K個ずつを使って辺重み計算
        REP(h,N-1){
            pair<int,int> next_ = make_pair(h+1,w);
            pair<int,int64> info_nears = sub_pairs(cumsum[min(N-1, h+cost_range)], cumsum[max(0, h-cost_range)]); //前後K個での和

            REP(_,coef){
                info_nears = add_pairs(info_nears, estimated_edge[encode(h,w)][encode(next_)]); //自分の辺の情報は重めに評価する
            }

            add_edge_by_nears(encode(h,w), encode(next_), info_nears, edge, init_cost);
        }   
    }
    
    return edge;    
}

void show_edge(vector<vector<pair<int,int64>>> const& edge){
    vector<vector<int64>> edge_h(N, vector<int64>(N, -1)), edge_w(N, vector<int64>(N, -1));
    REP(node,node_num){
        int h,w; tie(h,w) = decode(node);
        for(auto e:edge[node]){
            int to; int64 cost;
            tie(to,cost) = e;
            int to_h, to_w; tie(to_h,to_w)=decode(to);
            if(to_h-h == 1){
                edge_h[h][w] = cost;
            }else if(to_w-w == 1){
                edge_w[h][w] = cost;
            }
        }
    }

    cerr << "\n";
    REP(h,N){
        cerr << h << ":";
        REP(w,N){
            cerr << edge_h[h][w] << " ";
        } cerr << "\n";
    }

    cerr << "\n";
    REP(h,N){
        cerr << h << ":";
        REP(w,N){
            cerr << edge_w[h][w] << " ";
        } cerr << "\n";
    }

}

void re_eval_costs(int source, int target, string ans, int given_path_length, vector<vector<pair<int,int64>>> & estimated_edge){

    vector<int> RunLength;
    char before = ' ';
    for(auto move:ans){
        if(move == before) RunLength.back()++;
        else RunLength.emplace_back(1);
        before = move;
    }
    // debug(ans)
    // debug(RunLength)

    int now_position = source;
    int idx = 0;
    before = ans[0];
    for(char move:ans){
        if(before!=move){
            idx++;
            before = move;
        }
        int64 coef = 1000000LL*RunLength[idx]*RunLength[idx]/(ans.size()*ans.size()); //行動の中でその行/列の辺をどれだけ使っているか

        int now_h,now_w,to_h,to_w;
        tie(now_h, now_w) = decode(now_position);
        
        int dh,dw;
        if(move=='R'){
            dh = 0; dw = 1;
        }else if(move=='L'){
            dh = 0; dw = -1;
        }else if(move=='D'){
            dh = 1; dw = 0;
        }else{
            dh = -1; dw = 0;
        }

        to_h = now_h + dh;
        to_w = now_w + dw;

        int cnt = estimated_edge[now_position][encode(to_h, to_w)].first + coef * 1;
        int64 cost_sum = estimated_edge[now_position][encode(to_h, to_w)].second + (coef * given_path_length/ans.size());
        estimated_edge[now_position][encode(to_h, to_w)] = mp(cnt, cost_sum);
        estimated_edge[encode(to_h, to_w)][now_position] = mp(cnt, cost_sum);
        assert(cost_sum >= 0);
        assert(cnt >= 0);

        now_position = encode(to_h, to_w);
    }

    // debug(mp(ans, RunLength))
    assert(now_position == target); 
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    const int Query_num = 1000;
    vector<vector<pair<int,int64>>> estimated_edge(N*N, vector<pair<int,int64>>(N*N, mp(0,0))); //estimated_edge[u][v]:u,vを結ぶ辺の評価回数と重み合計

    REP(query,Query_num){
        // debug(query)
        pair<int,int> source, target;
        auto edge = get_edge(estimated_edge);
        // show_edge(edge);
        cin >> source.first >> source.second >> target.first >> target.second;
        // debug(source)
        // debug(target)
        string ans = solve(encode(source), encode(target), edge, query, estimated_edge);
        cout << ans << endl;
        int given_path_length; cin >> given_path_length;
        // debug(given_path_length)
        re_eval_costs(encode(source), encode(target), ans, given_path_length, estimated_edge);
    }


}

/*
    クエリ * (dijkstra + 辺重み再編成)

    各辺の推定重みはちゃんと保存しておくんだけど、そのクエリに対する辺重み計算するときに以下のことをする

    情報のある辺も近くの辺の情報を使って計算(自分の辺情報を優先)
    



    100ケース
    first_servey:25
    first_servey:50
    average 930228553.65
    first_servey:75
    average 931127898.27
    first_servey:100
    average 931523932.84
    first_servey:125
    average 928318009.42
    first_servey:150
    average 927177574.13

    1000ケース

    init_cost:3000
    cost_range:8
    coef:5
*/