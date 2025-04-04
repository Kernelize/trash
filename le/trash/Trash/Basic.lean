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

/- #eval (⟨0, Nat.zero_lt_succ 0⟩ : positive_nat) -/

def loo : IO Unit := do
  let mut sum := 0
  for i in List.range 101 do
    sum := sum + i
  IO.println sum

/- inductive Vec : Nat → Type → Type -/
/-   | nil : Vec 0 α -/
/-   | cons : ∀ {n : Nat} (a : α) (v : Vec n α), Vec (Nat.succ n) α -/

def natOrStringThree (b : Bool) : if b then Nat else String :=
  match b with
  | true => (3 : Nat)
  | false => "three"

def readBool : IO Bool := do
let stdin ← IO.getStdin
let input ← stdin.getLine
  return match input.trim with
    | "true" => true
    | _ => false

/- def main : IO Unit := do -/
/-   let b ← readBool -/
/-   let result : if b then Nat else String := natOrStringThree b -/
/-   IO.println result -/
