// trivial PLT caller

#define N (1 << 27)

extern void lib();

int main(int argc, char **argv) 
{
  int i;
  for (i = 0; i < N; i++) {
	lib();
  }
  return 0;
}

