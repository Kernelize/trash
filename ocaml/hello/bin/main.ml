let () = print_endline "Hello, World!"
let rec range lo hi = if lo > hi then [] else lo :: range (lo + 1) hi
let r = range 2 5;;

2.0 +. 2.0;;
float_of_int 1 +. 2.5

let rec sum l = match l with [] -> 0 | h :: t -> h + sum t
let rec length list = match list with [] -> 0 | _ :: t -> 1 + length t

type person = { first_name : string; surname : string; age : int }

let r = ref 0;;

r := 42
