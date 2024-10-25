import Mathlib.Algebra.Field.Defs
import Trash.Basic

open Classical

noncomputable section

def main : IO Unit := do
  let stdin ← IO.getStdin
  let stdout ← IO.getStdout

  stdout.putStrLn "How would you like to be addressed?"
  let input ← stdin.getLine
  let name := input.dropRightWhile Char.isWhitespace

  stdout.putStrLn s!"Hello, {name}!"

/- theorem complex_cannot_be_ordered_field : ¬ Nonempty -/
