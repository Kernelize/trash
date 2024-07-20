= Set theorem

+ let $A = {a_1, a_2, ..., a_n}$, $forall x, (x in <=> exists i(1 <= i <= n and x = a_i))$
+ $A = B <=> (forall x (x in A => x in B) and forall y(y in B => y in A))$
+ $exists emptyset(forall x(x in.not emptyset))$
+ $x in A union B <=> (x in A or x in B)$
+ (分类公理)$exists B. forall y. (y in B <=> (y in A and P(y)))$
+ (替换公理)$exists B. forall z.(z in B <=> (exists x in A, P(x, z)))$ \
  // 换句话说，使得对于每个$x in A$存在至少一个$y$, 使$P(x, y)$成立 $=>$

== Definitions
+ $A subset.eq B <=> forall x. x in A => x in B$
+ $A subset.neq B <=> A subset.eq B and A eq.not B$
+ $A \\ B := {x in A : x in.not B}$

== Function
