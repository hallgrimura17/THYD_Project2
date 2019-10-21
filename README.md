Appendix - Grammar
- [ ] ``` <program> ::= program <identifier> ; <main	block> . ```
- [ ] ``` <main	block> ::= <variable	declarations> <callable declarations> ``` <statements>
- [ ] ``` <variable	declarations> ::= 		<empty> ``` 
|	var	<variable	declaration> ; {	<variable	declaration> ; }
- [ ] ``` <variable	declaration> ::= <identifier> {	, <identifier> }	: <type>``` 
- [ ] ``` <type> ::= <simple	type> |	<array	type>``` 
- [ ] ``` <array	type> ::= array [ <index	range> ] of <simple	type>``` 
- [ ] ``` <index	range> ::= <integer	constant> .. <integer	constant>``` 
- [ ] ``` <simple	type> ::= integer |	boolean | real``` 
- [ ] ``` <callable	declarations> ::= {	<procedure	declaration> |	<function	``` declaration> }
- [ ] ``` <procedure	declaration> ::= procedure <procedure identifier> <opt	params> ; <block> ; ``` 
- [ ] ``` <function	declaration> ::= function <function identifier> <opt	params> : <simple	type> ; <block> ; ``` 
- [ ] ``` <opt	params> ::= <empty> |	( <parameter	list> { ; <parameter list> } )``` 
- [ ] ``` <parameter list> ::= <identifier> {	, <identifier> }	: <simple	type>```
- [ ] ``` <block> ::= <variable	declarations> <statements>```
- [ ] ``` <statements> ::= <compound	statement>```
- [ ] ``` <compound	statement> ::= begin <statement> {	; <statement> }	end```
- [ ] ``` <statement> ::= <simple	statement> |	<structured	statement>```
- [ ] ``` <simple	statement> ::= 		<assignment	statement>
|	<procedure	statement>
| <read	statement>
|	<write	statement>
|	<empty statement> ```
- [ ] ``` <empty statement> ::= <empty> ```
- [ ] ``` <assignment	statement> ::= 		<variable lvalue> := <expression>```
|	<function	identifier> := <expression> ```
- [ ] ``` <procedure	statement> ::= <procedure identifier> <optional	arguments>```
- [ ] ``` <read	statement> ::= read ( <input	variable> ) |	readln ( <input	variable> )```
- [ ] ``` <input	variable> ::= <variable lvalue>```
- [ ] ``` <write	statement> ::= write	( <output	value ) |	writeln ( <output	value> )```
- [ ] ``` <output	value> ::= <string	constant>	|	<expression>```
- [ ] ``` <structured	statement> ::= <compound	statement>
|	<if	statement>
|	<while	statement>```
- [ ] ``` <if	statement> ::= 		if <expression> then <statement>
|	if <expression> then <statement> else <statement>```
- [ ] ``` <while	statement> ::= while <expression> do <statement>```
- [ ] ``` <expression> ::= 		<simple	expression>
|	{	<simple	expression> <rel	op> <simple	expression> }```
- [ ] ``` <simple	expression> ::= <term> {	<add	op> <term> }```
- [ ] ``` <term> ::= <complemented	factor> {	<mult	op> <complemented	factor> }```
- [ ] ``` <complemented	factor> ::=	 <signed	factor> |	not <signed	factor>```
- [ ] ``` <signed	factor> ::=	 <factor> |		<sign> <factor>```
- [ ] ``` <factor> ::= <variable rvalue> |	<constant> | ( <expression> ) |		<function	call>```
- [ ] ``` <function	call> ::= <function identifier> <optional	arguments>```
- [ ] ``` <optional	arguments> ::= <empty> |	( <argument> { ,	<argument> } )```
- [ ] ``` <argument> ::= <expression>```
- [ ] ``` <rel op> ::= = |	<> |	< |	<= |	>= |	>```
- [ ] ``` <add op> ::= + |	- |	or```
- [ ] ``` <mult op> ::= * |	/ |	div |	and```
- [ ] ``` <sign> ::= + |	-```
- [ ] ``` <variable lvalue> ::= <variable>```
- [ ] ``` <variable rvalue> ::= <variable>```
- [ ] ``` <variable> ::= <entire	variable> |	<indexed	variable>```
- [ ] ``` <indexed	variable> ::= <array	variable> [ <expression> ]```
- [ ] ``` <array	variable> ::= <entire	variable>```
- [ ] ``` <entire	variable> ::= <variable	identifier>```
- [ ] ``` <variable	identifier> ::= <identifier>```
- [ ] ``` <procedure	identifier> ::= <identifier>```
- [ ] ``` <function	identifier> ::= <identifier>```
- [ ] ``` <constant> ::= <integer	constant> | <real	constant>| <boolean	consta```nt>
- [ ] ``` <integer	constant> ::= <integer>```
- [ ] ``` <real	constant> ::= <real>```
- [ ] ``` <boolean	constant> ::= true | false```
- [ ] ``` <string constant> ::= <string>```
- [X] ``` <empty> ::=```