#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<time.h>
const int N = 1000000;
int equiv_class[N+1];
int seen[N+1];
void compute(int n) {
  equiv_class[0]=equiv_class[1]=0;
  for (int i=0;i<=n;++i) seen[i]=0;
  for (int i=2;i<=n;++i) {
    for (int a=i-2,b=0;a>=b;--a,++b) {
      seen[equiv_class[a]^equiv_class[b]]=i;
    }
    int j=0; while (seen[j]==i) ++j;
    equiv_class[i]=j;
  }
}
void project(int start, int end) {
  for (int i=start;i<=end;++i) {
    equiv_class[i] = equiv_class[i-34];
  }
}
void init_solver(void) {
  compute(100);
  project(100,N);
}
int equiv(std::vector<int> const & v) {
  int result = 0;
  for (int i=0,j=v.size();i<j;++i) result^=equiv_class[v[i]];
  return result;
}



#define BUFFER_SIZE 1000
char s[BUFFER_SIZE];
void read_line(const char* msg = NULL) {
  if (msg) printf("%s",msg);
  int bufflen=0;
  while (true) {
    char c = getc(stdin);
    if (c=='\n') break;
    else s[bufflen++]=c;
  }
  s[bufflen]='\0';
}
int get_integer(const char* msg) {
  read_line(msg);
  int result = 0; char c;
  while (sscanf(s,"%d%c",&result,&c) != 1) {
    printf("Please enter a number.\n");
    read_line(msg);
  }
  return result;
}
int get_integer(const char* msg, int lowest, int highest) {
  int result = get_integer(msg);
  while (result < lowest || result > highest) {
    printf("Please enter a number between %d and %d.\n",lowest,highest);
    result = get_integer(msg);
  }
  return result;
}
void draw_board(const bool* b, int len) {
  printf("Current Board: [");
  for (int i=0;i<len;++i) printf("%c",b[i]?'#':'.');
  printf("]\n");
}
void draw_helper(const bool* b, int len) {
  printf("Available:      ");
  for (int i=0;i<len-1;++i) {
    if (!b[i]&&!b[i+1]) printf("%d",(i+1)%10);
    else printf(" ");
  }
  printf("\n");
  printf("                ");
  for (int i=0;i<len-1;++i) {
    if (!b[i]&&!b[i+1] && i>=9) printf("%d",(i+1)/10);
    else printf(" ");
  }
  printf("\n");
}
bool has_move(const bool* b, int len) {
  for (int i=0;i<len-1;++i) if (!b[i]&&!b[i+1]) return true;
  return false;
}
int make_move(bool* b, int len, int pos) {
  if (pos<0 || pos+1>=len) return 1;
  if (b[pos] || b[pos+1]) return 2;
  b[pos]=b[pos+1]=true;
  return 0;
}
int equiv(const bool* b, int len) {
  int so_far = 0;
  std::vector<int> segments;
  for (int i=0;i<len;++i) {
    if (!b[i]) ++so_far;
    else if (so_far > 0) {
      segments.push_back(so_far);
      so_far = 0;
    }
  }
  if (so_far > 0) segments.push_back(so_far);;
  return equiv(segments);
}
int comp_move(const bool* sb, int len) {
  std::vector<int> moves;
  for (int i=0;i<len-1;++i) if (!sb[i]&&!sb[i+1]) moves.push_back(i);
  int c = equiv(sb,len);
  if (c==0) return moves[rand()%moves.size()];
  else {
    bool* b = new bool[len];
    for (int i=0;i<len;++i) b[i]=sb[i];
    std::vector<int> good_moves;
    for (int i=0;i<moves.size();++i) {
      int p = moves[i];
      b[p]=b[p+1]=true;
      int newc = equiv(b,len);
      if (newc == 0) good_moves.push_back(p);
      b[p]=b[p+1]=false;
    }
    delete b;
    return good_moves[rand()%good_moves.size()];
  }
}
void rungame(int pieces) {
  bool* board = new bool[pieces];
  for (int i=0;i<pieces;++i) board[i]=false;
  char move_request[100];
  sprintf(move_request,"Enter a move (between %d and %d): ",1,pieces-1);
  while (true) {
    if (!has_move(board,pieces)) {
      draw_board(board,pieces);
      printf("You have no legal moves left! The computer wins!\n\n");
      break;
    }
    while (true) {
      printf("\n");
      draw_board(board,pieces);
      draw_helper(board,pieces);
      bool success = false;
      int pos = get_integer(move_request,1,pieces-1);
      switch(make_move(board,pieces,pos-1)) {
        case 1:
          printf("You cannot move there. Move is outside of boundary.\n");
          success=false;
          break;
        case 2:
          printf("You cannot move there. There is already a piece there.\n");
          success=false;
          break;
        default:
          printf("\nYou moved at position %d.\n",pos);
          draw_board(board,pieces);
          success=true;
          break;
      }
      if (success) break;
    }
    if (!has_move(board,pieces)) {
      printf("The computer has no legal moves left! You win!\n\n");
      break;
    }
    int cpos = comp_move(board,pieces);
    make_move(board,pieces,cpos);
    printf("\nThe computer moved at position %d.\n",cpos+1);
  }
  delete board;
}
int main (void) {
  srand(time(NULL));
  init_solver();
  while(true) {
    printf("\n\nWelcome to the domino game!\n");
    printf("Players take turn placing dominoes until no moves remain.\n");
    printf("The objective of the game is to place the last domino.\n\n");
    int pieces = get_integer("Enter board size: ",2,100);
    rungame(pieces);
  }
  return 0;
}