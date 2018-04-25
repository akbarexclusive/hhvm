open Ide_api_types

type connection_type =
  | Persistent
  | Non_persistent

type connection_response =
  | Connected

type status_liveness =
  | Stale_status
  | Live_status

module Server_status = struct
  type t = {
    liveness : status_liveness;
    has_unsaved_changes : bool;
    error_list : Pos.absolute Errors.error_ list;
  }
end

module Ignore_fixmes_result = struct
  type t = {
    has_unsaved_changes : bool;
    error_list : Pos.absolute  Errors.error_ list;
  }
end

module Identify_symbol = struct
  type single_result = (string SymbolOccurrence.t) * (string SymbolDefinition.t option)
  type result = single_result list
end

module Method_jumps = struct
  type result = {
    orig_name: string;
    orig_pos: Pos.absolute;
    dest_name: string;
    dest_pos: Pos.absolute;
    orig_p_name: string; (* Used for methods to find their parent class *)
    dest_p_name: string;
  }

  type filter =
    | No_filter
    | Class
    | Interface
    | Trait
end

module Find_refs = struct
  type member = Ai.ServerFindRefs.member =
    | Method of string
    | Property of string
    | Class_const of string
    | Typeconst of string

  type action = Ai.ServerFindRefs.action =
    | Class of string
    | Member of string * member
    | Function of string
    | GConst of string

    type result = (string * Pos.absolute) list
    type ide_result = (string * Pos.absolute list) option
end

module Symbol_type = struct
  type t = {
    pos: string Pos.pos;
    type_: string;
    ident_: int;
  }
end

module Symbol_info_service = struct
  type target_type =
    | Function
    | Method
    | Constructor

  type symbol_fun_call = {
    name:  string;
    type_: target_type;
    pos: string Pos.pos;
    caller: string;
  }

  type result = {
    fun_calls: symbol_fun_call list;
    symbol_types: Symbol_type.t list;
  }
end

module Outline = struct
  type outline = string SymbolDefinition.t list
end

module Infer_return_type = struct
  type t =
  | Function of string
  | Method of string * string

  type result = (string, string) Pervasives.result
end

type file_input =
  | FileName of string
  | FileContent of string

type lint_stdin_input = { filename: string; contents: string }

(* The following datatypes can be interpreted as follows:
 * MESSAGE_TAG : Argument type (sent from client to server) -> return type t *)
type _ t =
  | STATUS : bool -> Server_status.t t
  | INFER_TYPE : file_input * int * int * bool ->
      InferAtPosService.result t
  | INFER_TYPE_BATCH : (string * int * int * (int * int) option) list * bool -> string list t
  | TYPED_AST : string -> string t
  | IDE_HOVER : file_input * int * int ->
      HoverService.result t
  | DOCBLOCK_AT : (string * int * int * string option) -> DocblockService.result t
  | COVERAGE_LEVELS : file_input -> Coverage_level.result t
  | AUTOCOMPLETE : string -> AutocompleteTypes.result t
  | IDENTIFY_FUNCTION : file_input * int * int ->
      Identify_symbol.result t
  | METHOD_JUMP : (string * Method_jumps.filter * bool) ->
      Method_jumps.result list t
  | FIND_DEPENDENT_FILES: string list -> string list t
  | FIND_REFS : Find_refs.action -> Find_refs.result t
  | IDE_FIND_REFS : file_input * int * int * bool ->
      Find_refs.ide_result t
  | IDE_HIGHLIGHT_REFS : file_input * int * int ->
      ServerHighlightRefsTypes.result t
  | REFACTOR : ServerRefactorTypes.action -> ServerRefactorTypes.patch list t
  | IDE_REFACTOR : file_input * int * int * string ->
      ServerRefactorTypes.patch list t
  | DUMP_SYMBOL_INFO : string list -> Symbol_info_service.result t
  | DUMP_AI_INFO : string list -> Ai.InfoService.result t
  | REMOVE_DEAD_FIXMES : int list -> [`Ok of ServerRefactorTypes.patch list | `Error of string] t
  | IGNORE_FIXMES : string list -> Ignore_fixmes_result.t t
  | IN_MEMORY_DEP_TABLE_SIZE : ((int, string) Pervasives.result) t
  | SAVE_STATE : string -> ((int, string) Pervasives.result) t
  | SEARCH : string * string -> HackSearchService.result t
  | COVERAGE_COUNTS : string -> ServerCoverageMetricTypes.result t
  | LINT : string list -> ServerLintTypes.result t
  | LINT_STDIN : lint_stdin_input -> ServerLintTypes.result t
  | LINT_ALL : int -> ServerLintTypes.result t
  | CREATE_CHECKPOINT : string -> unit t
  | RETRIEVE_CHECKPOINT : string -> string list option t
  | DELETE_CHECKPOINT : string -> bool t
  | STATS : Stats.t t
  | KILL : unit t
  | FORMAT : ServerFormatTypes.action -> ServerFormatTypes.result t
  | HH_FORMAT : Lsp.TextDocumentItem.t SMap.t * ServerFormatTypes.ide_action * bool -> ServerFormatTypes.ide_result t
  | TRACE_AI : Ai.TraceService.action -> string t
  | AI_QUERY : string -> string t
  | DUMP_FULL_FIDELITY_PARSE : string -> string t
  | OPEN_FILE : string * string -> unit t
  | CLOSE_FILE : string -> unit t
  | EDIT_FILE : string * (text_edit list) -> unit t
  | IDE_AUTOCOMPLETE : string * position * bool -> AutocompleteTypes.ide_result t
  | IDE_FFP_AUTOCOMPLETE : string * position -> AutocompleteTypes.ide_result t
  | DISCONNECT : unit t
  | SUBSCRIBE_DIAGNOSTIC : int -> unit t
  | UNSUBSCRIBE_DIAGNOSTIC : int -> unit t
  | OUTLINE : string -> Outline.outline t
  | IDE_IDLE : unit t
  | INFER_RETURN_TYPE : Infer_return_type.t ->
      Infer_return_type.result t
  | RAGE : ServerRageTypes.result t
  | DYNAMIC_VIEW: bool -> unit t

let is_disconnect_rpc : type a. a t -> bool = function
  | DISCONNECT -> true
  | _ -> false

let is_kill_rpc : type a. a t -> bool = function
  | KILL -> true
  | _ -> false

let is_critical_rpc : type a. a t -> bool = function
  (* An exception during any critical rpc should shutdown the persistent connection. *)
  (* The critical ones are those that affect the state.                              *)
  | DISCONNECT -> true
  | KILL -> true
  | CREATE_CHECKPOINT _ -> true
  | DELETE_CHECKPOINT _ -> true
  | OPEN_FILE _ -> true
  | CLOSE_FILE _ -> true
  | EDIT_FILE _ -> true
  | SUBSCRIBE_DIAGNOSTIC _ -> true
  | UNSUBSCRIBE_DIAGNOSTIC _ -> true
  | _ -> false

type 'a command =
  | Rpc of 'a t
  | Stream of streamed
  | Debug

and streamed =
  | SHOW of string
  | LIST_FILES
  | LIST_MODES
  | BUILD of ServerBuild.build_opts

type push =
  | DIAGNOSTIC of int * (Pos.absolute Errors.error_ list) SMap.t
  | BUSY_STATUS of busy_status
  | NEW_CLIENT_CONNECTED
  | FATAL_EXCEPTION of Marshal_tools.remote_exception_data
  | NONFATAL_EXCEPTION of Marshal_tools.remote_exception_data

and busy_status =
  | Needs_local_typecheck
  | Doing_local_typecheck
  | Done_local_typecheck
  | Doing_global_typecheck
  | Done_global_typecheck

type 'a persistent_connection_message_type =
  | Push of push
  | Response of 'a * float (* records the time at which hh_server started handling *)
  | Hello
  (* Hello is the first message sent after handoff. It's used for both *)
  (* persistent and non-persistent connections. It's included in this  *)
  (* type, though, because ocaml typing forces a single type to come   *)
  (* Marshal.from_fd_with_preamble.                                    *)
  | Ping
  (* Pings can be sent to non-persistent connection after Hello and before
   * sending RPC response. *)

(** Timeout on reading the command from the client - client probably frozen. *)
exception Read_command_timeout
