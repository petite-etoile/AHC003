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



vector<int> dijkstra(vector<vector<pair<int,int64>>> const& edge, int start){
    vector<int64> distances(node_num,INF);
    priority_queue<pair<int64,int>,vector<pair<int64,int>>, greater<pair<int64,int>> > que;
    que.push(mp(0, start));
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
    // debug(distances)
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

string solve(int const& source, int const& target, vector<vector<pair<int,int64>>> const& edge){
    auto move_from = dijkstra(edge, source);
    string ans = encode_to_ans(source, target, move_from);
    return ans;
}

pair<int,int64> add_pairs(pair<int,int64> const& A, pair<int,int64> const& B){
    return make_pair(A.first+B.first, A.second+B.second);
}

pair<int,int64> sub_pairs(pair<int,int64> const& A, pair<int,int64> const& B){
    return make_pair(A.first-B.first, A.second-B.second);
}


bool flag = false;
vector<vector<pair<int,int64>>> get_edge(vector<vector<pair<int,int64>>> const& estimated_edge){
    const int64 init_cost = 2000; //考慮するべき
    vector<vector<pair<int,int64>>> edge(node_num);

    const int K = 8; //前後何個の情報で辺の重みを決定するか


    if(!flag){
        flag = true;
        cerr << "パラメータ\n";
        debug(K)
        debug(init_cost)
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
            pair<int,int64> info_nears = sub_pairs(cumsum[min(N-1, w+K)], cumsum[max(0, w-K)]); //前後K個での和
            
            if(info_nears == mp(0,0LL)){
                edge[encode(next_)].emplace_back(encode(h,w), init_cost);
                edge[encode(h,w)].emplace_back(encode(next_), init_cost);
            }else{
                edge[encode(next_)].emplace_back(encode(h,w), info_nears.second / info_nears.first);
                edge[encode(h,w)].emplace_back(encode(next_), info_nears.second / info_nears.first);
            }
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
            pair<int,int64> info_nears = sub_pairs(cumsum[min(N-1, h+K)], cumsum[max(0, h-K)]); //前後K個での和
            
            if(info_nears == mp(0,0LL)){
                edge[encode(next_)].emplace_back(encode(h,w), init_cost);
                edge[encode(h,w)].emplace_back(encode(next_), init_cost);
            }else{
                edge[encode(next_)].emplace_back(encode(h,w), info_nears.second / info_nears.first);
                edge[encode(h,w)].emplace_back(encode(next_), info_nears.second / info_nears.first);
            }
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
        REP(w,N){
            cerr << edge_h[h][w] << " ";
        } cerr << "\n";
    }

    cerr << "\n";
    REP(h,N){
        REP(w,N){
            cerr << edge_w[h][w] << " ";
        } cerr << "\n";
    }

}

void re_eval_costs(int source, int target, string ans, int given_path_length, vector<vector<pair<int,int64>>> & estimated_edge){
    int now_position = source;
    for(char move:ans){
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

        // debug(move)
        // debug(decode(now_position))

        to_h = now_h + dh;
        to_w = now_w + dw;

        int cnt = estimated_edge[now_position][encode(to_h, to_w)].first + 1;
        int64 cost_sum = estimated_edge[now_position][encode(to_h, to_w)].second + given_path_length/ans.size();
        estimated_edge[now_position][encode(to_h, to_w)] = mp(cnt, cost_sum);
        estimated_edge[encode(to_h, to_w)][now_position] = mp(cnt, cost_sum);

        now_position = encode(to_h, to_w);
    }
    assert(now_position == target); 
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    const int Query_num = 1000;
    vector<vector<pair<int,int64>>> estimated_edge(N*N, vector<pair<int,int64>>(N*N, mp(0,0))); //estimated_edge[u][v]:u,vを結ぶ辺の評価回数と重み合計

    REP(_,Query_num){
        pair<int,int> source, target;
        auto edge = get_edge(estimated_edge);
        // show_edge(edge);
        cin >> source.first >> source.second >> target.first >> target.second;
        // debug(_)
        string ans = solve(encode(source), encode(target), edge);
        cout << ans << endl;
        int given_path_length; cin >> given_path_length;
        re_eval_costs(encode(source), encode(target), ans, given_path_length, estimated_edge);
    }


}

/*
    クエリ * (dijkstra + 辺重み再編成)

    各辺の推定重みはちゃんと保存しておくんだけど、そのクエリに対する辺重み計算するときに以下のことをする

    情報のある辺も近くの辺の情報を使って計算


    100ケース
    average 919111364.12
    1000ケース
    ?


*/