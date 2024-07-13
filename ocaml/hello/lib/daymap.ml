type day = Mon | Tue | Wed | Thu | Fri | Sat | Sun

let int_of_day = function
  | Mon -> 1
  | Tue -> 2
  | Wed -> 3
  | Thu -> 4
  | Fri -> 5
  | Sat -> 6
  | Sun -> 7

module DayKey = struct
  type t = day

  let compare day1 day2 = int_of_day day1 - int_of_day day2
end

module DayMap = Map.Make (DayKey)

let () =
  let open DayMap in
  let m = empty in
  let m = add Mon 1 m in
  let m = add Tue 2 m in
  let m = add Wed 3 m in
  let m = add Thu 4 m in
  Printf.printf "%d\n" (find Mon m);
  Printf.printf "%d\n" (find Tue m);
  Printf.printf "%d\n" (find Wed m);
  Printf.printf "%d\n" (find Thu m)
