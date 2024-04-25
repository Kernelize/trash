struct Foo {
  int x;
  int y;
};

int func(struct Foo *foo) {
  return foo->x + foo->y;
}

