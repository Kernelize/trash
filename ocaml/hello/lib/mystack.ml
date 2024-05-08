type 'a t = 'a list

exception Empty

let empty = []
let is_empty = function [] -> true | _ -> false
let push x s = x :: s
let peek = function [] -> raise Empty | x :: _ -> x
let pop = function [] -> raise Empty | _ :: s -> s
let size = List.length

let pp pp_val fmt s =
  let open Format in
  let pp_break fmt () = fprintf fmt "@," in
  fprintf fmt "@[<v 0>top of stack]";
  if s <> [] then fprintf fmt "@,";
  pp_print_list ~pp_sep:pp_break pp_val fmt s;
  fprintf fmt "@,bottom of stack@]"

let to_list = Fun.id
