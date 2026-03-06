package qdocparser

// #cgo CFLAGS: -std=c11 -fPIC
// #include "tree_sitter/parser.h"
// TSLanguage *tree_sitter_qdoc(void);
import "C"

import (
	"unsafe"

	sitter "github.com/smacker/go-tree-sitter"
)

// GetLanguage returns the tree-sitter Language for QDoc.
func GetLanguage() *sitter.Language {
	return sitter.NewLanguage(unsafe.Pointer(C.tree_sitter_qdoc()))
}
