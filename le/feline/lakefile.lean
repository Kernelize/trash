import Lake
open Lake DSL

package "feline" where
  version := v!"0.1.0"

lean_lib «Feline» where
  -- add library configuration options here

@[default_target]
lean_exe "feline" where
  root := `Main
