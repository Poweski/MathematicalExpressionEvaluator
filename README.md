# Mathematical_Expression_Evaluator

(third Effective Programming Techniques project)

## Comments:
- The program allows you to load mathematical formulas, interpret them in the form of a tree and calculate values.
- Mathematical formulas are provided to the program input in prefix form.
- Communication with the program takes place via the console.
- An expression can contain operation symbols, variables, and numbers.
- Supported operation types: _+, -, *, /, sin, cos_.
- Variable names consist of uppercase and lowercase letters and numbers.
- If there is an illegal value in the string, e.g. _$_, we ignore it.
- The variable name must contain at least one letter.
- Numbers consist only of digits and can only be positive.
- We assume that individual parts of the expression are separated from each other by at least one space.
- The program corrects expressions by completing missing elements and omitting redundant ones.
   For example, if the expression _+ + +_ is entered, the expression will be repaired to: _+ 1 + 1 + 1 1_.
- Joining trees: If we join tree A with tree B, it means that instead of the last leaf of tree A we insert the root of tree B.

## Commands:
- **enter \<formula>** - Execution attempts to create a tree based on the given expression. If the expression cannot be loaded because it contains errors, the program completes the tree so that the tree is correct.
- **vars** - Prints all variables from the currently entered tree. Each variable is printed once, even if it appears more than once in the tree.
- **print** - Prints the currently entered tree in prefix form.
- **comp \<var0> \<var1>…\<varN>** – Calculation of the value of the entered formula, where \<var0> \<var1>…\<varN> are the values for subsequent variables in the tree. The values correspond to the variables in the order in which the variables are printed by the vars command.
- **join \<formula>** - Execution attempts to create a tree based on the given expression. Then the created tree is added to the existing tree.

# Main classes:
- **Mediator** - Responsible for communication with the user and tree management.
- **Tree** - Stores nodes.
- **Node** - Responsible for a single element of the expression. Reads and detects errors in the entered formula.
