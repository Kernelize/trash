def hello := "world"

def add1 (x : Nat) : Nat := x + 1

#eval add1 10

def α := 10

#eval 1 + 2

#eval String.append "hello " "world"

#eval String.append "hello " (String.append "world" "!")

#eval String.append "it is" (if 1 > 2 then "not " else "") ++ "true"

#eval (1 - 2 : Int)

#check (1 - 2 : Int)

def lean : String := "Lean"

def maximum (x y : Nat) : Nat :=
  if x > y then x else y

#check maximum
#check (maximum)

#eval maximum 10 20

def joinStringWith( s1 s2 s3 : String) : String :=
  s2 ++ s1 ++ s3

def volume(a b c : Nat) : Nat :=
  a * b * c

#check joinStringWith ":"

def Str : Type := String

def aStr : Str := "This is a string."

def NaturalNumber : Type := Nat

def thirtyEight : NaturalNumber := (38 : Nat)

structure Point where
  x : Float
  y : Float
deriving Repr

def origin : Point := { x := 0.0, y := 0.0 }

#eval origin
#eval (origin.x, origin.y)

def distance (p1 p2 : Point) : Float :=
  Float.sqrt ((p1.x - p2.x) ^ 2.0 + (p1.y - p2.y) ^ 2.0)

def zeroX (p : Point) : Point := { p with x := 0.0}

def Point.modifyBoth (f : Float → Float) (p : Point) : Point :=
  { x := f p.x, y := f p.y }

structure Book where
  makeBook ::
  title : String
  author : String
  price : Float

inductive MyBool where
  | ttrue : MyBool
  | ffalse : MyBool

def isZero (n : Nat) : MyBool :=
  match n with
  | Nat.zero => MyBool.ttrue
  | Nat.succ _ => MyBool.ffalse

def depth (p: Point) : Float :=
  match p with
  | { x := h, y := w } => h + w

/- def evenLoops (n : Nat) : Bool := -/
/- match n with -/
/- | Nat.zero => true -/
/- | Nat.succ k => not (evenLoops n) -/

def plus (n : Nat) (k : Nat) : Nat :=
  match k with
  | Nat.zero => n
  | Nat.succ k' => Nat.succ (plus n k')

structure PPoint (α : Type) where
  x : α
  y : α
deriving Repr

def replaceX (α : Type) (point : PPoint α) (newX : α) : PPoint α :=
  { point with x := newX }

#check (PPoint)

inductive Sign where
  | pos
  | neg

def posOrNegThree (s : Sign) : match s with | Sign.pos => Nat | Sign.neg => Int :=
  match s with
  | Sign.pos => (3 : Nat)
  | Sign.neg => (-3 : Int)

def primesUnder10 : List Nat := [2, 3, 5, 7]

#check String

def distribute (α β γ : Type) (x : α × (β ⊕ γ)) : (α × β) ⊕ (α × γ) :=
  match x with
  | (a, Sum.inl b) => Sum.inl (a, b)
  | (a, Sum.inr c) => Sum.inr (a, c)

def distribute2 {α β γ : Type} : α × (β ⊕ γ) → (α × β) ⊕ (α × γ)
  | (a, Sum.inl b) => Sum.inl (a, b)
  | (a, Sum.inr c) => Sum.inr (a, c)

#check distribute2

/- def zip {α β : Type} : (List α × List β) → List (α × β) -/
/-   | [], _ => [] -/
/-   | _, [] => [] -/
/-   | x::xs, y::ys => (x, y) :: zip xs ys -/

def Prod.swap {α β : Type} (pair : α × β) : β × α :=
  match pair with
  | (a, b) => (b, a)

def List.findFirst? {α : Type} (xs : List α) (predicate : α → Bool) : Option α :=
  match xs with
  | [] => none
  | x::xs => if predicate x then some x else List.findFirst? xs predicate

def length {α : Type} (xs : List α) : Nat :=
  match xs with
  | [] => 0
  | _ :: ys => Nat.succ (length ys)


def length2 (α : Type) (xs : List α) : Nat :=
  match xs with
  | [] => 0
  | _ :: ys => Nat.succ (length2 α ys)

def Prod.swap2 {α β : Type} : α × β → β × α
  | (a, b) => (b, a)

def unzip {α β : Type}: List (α × β) → List α × List β
  | [] => ([], [])
  | (x, y) :: xys =>
    let unzipped := unzip xys
    (x :: unzipped.fst, y :: unzipped.snd)

#check λ x => x + 1

#check λ | 0 => none | x => some x

#check (· + 2)

namespace NewNamespace
def triple (x : Nat) : Nat := 3 * x
def quadruple (x : Nat) : Nat := 2 * x + 2 * x
end NewNamespace

/- inductive PosNat : Type -/
/- | mk : ∀ (n : ℕ), n > 0 → PosNat -/


def positive_nat := {n : Nat // n > 0}
#eval (⟨1, Nat.zero_lt_succ 0⟩ : positive_nat)

#eval "Hello!!!".dropRightWhile (· == '!')

def nTimes (action : IO Unit) : Nat -> IO Unit
  | 0 => pure ()
  | n + 1 => do
    action
    nTimes action n

def countdown : Nat -> List (IO Unit)
  | 0 => [IO.println "Blast off!"]
  | n + 1 => IO.println s!"{n + 1}" :: countdown n

def from5 : List (IO Unit) := countdown 5

#eval from5.length

def runActions : List (IO Unit) -> IO Unit
  | [] => pure ()
  | act :: actions => do
    act
    runActions actions

#eval runActions (countdown 3)

def main1 : IO Unit := do
  let (stdin, stdout) ← Prod.mk <$> IO.getStdin <*> IO.getStdout
  stdout.putStrLn "How would you like to be addressed?"
  let name := (← stdin.getLine).trim
  stdout.putStrLn s!"Hello, {name}"

theorem onePlusOneIsTwo : 1 + 1 = 2 := rfl

theorem onePlusOneIsTwo' : 1 + 1 = 2 := by
  simp

def woodlandCritters : List String :=
  ["hedgehog", "deer", "snail"]

/- def oops := woodlandCritters[3] -/

#eval woodlandCritters[3]!

/- theorem addAndAppend : 1 + 1 = 2 ∧ "Str".append "ing" = "String" := by simp -/

/- def unsafeThird { α : Type } (xs : List α) : α := xs[2] -/

def third { α : Type } (xs : List α) (ok : xs.length > 2) : α := xs[2]

class Plus (α : Type) where
  plus : α → α → α

instance : Plus Nat where
  plus := Nat.add

inductive Pos : Type where
  | one : Pos
  | succ : Pos → Pos
deriving Repr

def Pos.plus : Pos → Pos → Pos
  | Pos.one, k => Pos.succ k
  | Pos.succ n, k => Pos.succ (n.plus k)

instance : Plus Pos where
  plus := Pos.plus


instance : Add Pos where
  add := Pos.plus

instance : OfNat Pos (n + 1) where
  ofNat :=
    let rec natPlusOne : Nat → Pos
      | 0 => Pos.one
      | k + 1 => Pos.succ (natPlusOne k)
    natPlusOne n

def Pos.toNat : Pos → Nat
  | Pos.one => 1
  | Pos.succ n => n.toNat + 1

instance : ToString Pos where
  toString := toString ∘ Pos.toNat

def addNatPos : Nat -> Pos -> Pos
  | 0, p => p
  | n + 1, p => Pos.succ (addNatPos n p)

def addPosNat : Pos -> Nat -> Pos
  | p, 0 => p
  | p, n + 1 => Pos.succ (addPosNat p n)

instance : HAdd Nat Pos Pos where
  hAdd := addNatPos

instance : HAdd Pos Nat Pos where
  hAdd := addPosNat

#eval (3 : Pos) + (5 : Nat)

#check @OfNat.ofNat

def a := [1, 2, 3]

/- def b := a[3] -/

def eight : Pos := 8
#eval ((OfNat.ofNat 3) : Pos)
#eval eight

class HPlus (α : Type) (β : Type) (γ : outParam Type) where
  hPlus : α → β → γ

instance : HPlus Nat Pos Pos where
  hPlus := addNatPos

instance : HPlus Pos Nat Pos where
  hPlus := addPosNat

@[default_instance]
instance {α : Type} [Add α] : HPlus α α α where
  hPlus := Add.add

#check ((HPlus.hPlus (5 : Nat)) : Pos → Pos)

instance {α : Type} [Mul α] : HMul (PPoint α) α (PPoint α) where
  hMul p n := { x := p.x * n, y := p.y * n }

#eval (PPoint.mk 3 4) * 2

example (n : Nat) (k : Nat) : Bool :=
  n + k == k + n

