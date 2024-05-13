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

module type T = sig
  type t = int

  val x : t
end

module M : T = struct
  type t = int

  let x = 42
end

let a : int = M.x
let kupo_pp fmt s = Format.fprintf fmt "%s kupo" s

module ListStack = struct
  type 'a t = 'a list

  exception Empty

  let empty = []
  let is_empty = function [] -> true | _ -> false
  let push = List.cons
  let peek = function [] -> None | x :: _ -> Some x
  let pop = function [] -> None | _ :: s -> Some s
  let size = List.length
  let to_list = Fun.id
end

let ( >>| ) opt f = match opt with None -> None | Some x -> Some (f x)
let ( >>= ) opt f = match opt with None -> None | Some x -> f x

let _ =
  ListStack.(empty |> push 1 |> pop >>| push 2 >>= pop >>| push 3 >>| to_list)

module type Queue = sig
  type 'a t
  (** An ['a t] is a queue whose elements have type ['a]. *)

  exception Empty
  (** Raised if [front] or [dequeue] is applied to the empty queue. *)

  val empty : 'a t
  (** [empty] is the empty queue. *)

  val is_empty : 'a t -> bool
  (** [is_empty q] is whether [q] is empty. *)

  val enqueue : 'a -> 'a t -> 'a t
  (** [enqueue x q] is the queue [q] with [x] added to the end. *)

  val front : 'a t -> 'a
  (** [front q] is the element at the front of the queue. Raises [Empty]
      if [q] is empty. *)

  val dequeue : 'a t -> 'a t
  (** [dequeue q] is the queue containing all the elements of [q] except the
      front of [q]. Raises [Empty] is [q] is empty. *)

  val size : 'a t -> int
  (** [size q] is the number of elements in [q]. *)

  val to_list : 'a t -> 'a list
  (** [to_list q] is a list containing the elements of [q] in order from
      front to back. *)
end

(* module BatchedQueue : Queue = struct *)
(*   type 'a t = { o : 'a list; i : 'a list } *)
(**)
(*   exception Empty *)
(**)
(*   let empty = { o = []; i = [] } *)
(*   let is_empty = function { o = [] } -> true | _ -> false *)
(* end *)

type vec = float array

let vec_print v =
  for i = 0 to Array.length v - 1 do
    print_float v.(i);
    print_newline ()
  done

let vec_print' v = Array.iter (Printf.printf "%f\n") v
let v = [| 1.; 0. |]
let _ = v.(1) <- 2.

let vec_add v1 v2 =
  let len1, len2 = (Array.length v1, Array.length v2) in
  if len1 <> len2 then invalid_arg "different lengths"
  else Array.init len1 (fun x -> v1.(x) + v2.(x))

let vec_add' v1 v2 = Array.map2 ( +. ) v1 v2
