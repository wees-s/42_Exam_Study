VOCÊ ESTÁ CERTO! 😂
Markdown é muito mais simples e você pode:

✅ Copiar direto do chat
✅ Salvar como .md e abrir em qualquer editor
✅ Visualizar no GitHub, VSCode, Obsidian, etc.
✅ Converter pra PDF se quiser
✅ Abrir no celular em apps de markdown


🎯 GUIA VBC - CHEAT SHEET DEFINITIVO
🔑 AS TRÊS REGRAS DE OURO
1️⃣ AMP - A Ordem Sagrada
parse_expr()
    ↓
    A (Add)      ← chama Multi
    ↓
    M (Multi)    ← chama Primary
    ↓
    P (Primary)  ← SE '(' volta pro A (loop!)
                 ← SE dígito PARA (base)
Mnemônico: Add Multi Primary

2️⃣ TEMPLATE UNIVERSAL (Add e Multi)
cnode *parse_OPERADOR(char **s)
{
    node *left, *right, tmp;

    // 1. Pede ajuda
    left = chama_funcao_superior(s);
    if (!left)
        return (NULL);

    // 2. Loop: é comigo?
    while (**s == 'MEU_OPERADOR')
    {
        (*s)++;  // consome operador

        // 3. Pede ajuda de novo
        right = chama_funcao_superior(s);
        if (!right)
            return (destroy_tree(left), NULL);

        // 4. Cria nó e acumula
        tmp = (node){MEU_TIPO, 0, left, right};
        left = new_node(tmp);
    }

    // 5. Retorna acumulado
    return (left);
}

3️⃣ PRIMARY É ESPECIAL (Caso Base)
cnode *parse_primary(char **s)
{
    node *res, tmp;

    // CASO 1: Parêntese (reinicia AMP!)
    if (accept(s, '('))
    {
        res = parse_add(s);  // ← volta pro A
        if (!res || !expect(s, ')'))
            return (destroy_tree(res), NULL);
        return (res);
    }

    // CASO 2: Dígito (base!)
    if (isdigit(**s))
    {
        tmp = (node){VAL, **s - '0', NULL, NULL};
        (*s)++;
        return (new_node(tmp));
    }

    // CASO 3: Erro
    unexpected(**s);
    return (NULL);
}

📋 APLICANDO O TEMPLATE
parse_multi()
cnode *parse_multi(char **s)
{
    node *left, *right, tmp;

    left = parse_primary(s);  // ← funcao_superior
    if (!left)
        return (NULL);

    while (**s == '*')        // ← MEU_OPERADOR
    {
        (*s)++;
        right = parse_primary(s);
        if (!right)
            return (destroy_tree(left), NULL);
        tmp = (node){MULTI, 0, left, right};  // ← MEU_TIPO
        left = new_node(tmp);
    }
    return (left);
}
parse_add()
cnode *parse_add(char **s)
{
    node *left, *right, tmp;

    left = parse_multi(s);    // ← funcao_superior
    if (!left)
        return (NULL);

    while (**s == '+')        // ← MEU_OPERADOR
    {
        (*s)++;
        right = parse_multi(s);
        if (!right)
            return (destroy_tree(left), NULL);
        tmp = (node){ADD, 0, left, right};    // ← MEU_TIPO
        left = new_node(tmp);
    }
    return (left);
}
parse_expr()
cnode *parse_expr(char *s)
{
    node *res;

    res = parse_add(&s);  // ← inicia AMP

    // Valida que consumiu tudo
    if (res && *s)
    {
        unexpected(*s);
        return (destroy_tree(res), NULL);
    }
    return (res);
}

⚠️ CORREÇÃO OBRIGATÓRIA: accept()
c// ❌ VERSÃO BUGADA (fornecida no exame):
int accept(char **s, char c)
{
    if (**s)  // só verifica se não é '\0'
    {
        (*s)++;
        return (1);
    }
    return (0);
}

// ✅ VERSÃO CORRETA:
int accept(char **s, char c)
{
    if (**s == c)  // verifica se É o caractere
    {
        (*s)++;
        return (1);
    }
    return (0);
}
```

---

## 🧠 TRUQUES DE MEMORIZAÇÃO

### **1. AMP = Ordem de Chamadas**
- **A**dd chama **M**ulti chama **P**rimary
- Primary volta pro Add se achar `(`

### **2. Template = 5 Passos**
1. `left = superior()`
2. `while (meu_operador)`
3. `right = superior()`
4. `tmp = {TIPO, left, right}`
5. `left = new_node(tmp)`

### **3. Primary = Base ou Reset**
- Número → PARA (base)
- `(` → REINICIA (volta pro Add)

### **4. Ponteiro Duplo**
- `*s` = endereço
- `**s` = caractere atual
- `(*s)++` = avança ponteiro

### **5. Operador Vírgula**
- `(destroy_tree(left), NULL)` = limpa e retorna erro

---

## 📊 TABELA RESUMO

| Função | Chama | Operador | Tipo Nó |
|--------|-------|----------|---------|
| `parse_add` | `parse_multi` | `+` | `ADD` |
| `parse_multi` | `parse_primary` | `*` | `MULTI` |
| `parse_primary` | `parse_add` (se `(`) | - | `VAL` |

---

## 🔄 FLUXO RECURSIVO
```
Para "((3+4)*5)":

expr → add → multi → primary → '('
              ↓
           add → multi → primary → '('
                    ↓
                 add → multi → primary → '3' (BASE!)
                    ↑
                 volta montando (3+4)
              ↑
           volta montando ((3+4)*5)
       ↑
    retorna árvore completa
```

---

## ✅ CHECKLIST RÁPIDO

- [ ] Corrigir `accept()` com `**s == c`
- [ ] Implementar `parse_primary()` (2 casos + erro)
- [ ] Copiar template para `parse_multi()` (trocar `*`, `MULTI`, `primary`)
- [ ] Copiar template para `parse_add()` (trocar `+`, `ADD`, `multi`)
- [ ] Implementar `parse_expr()` (chama add e valida)
- [ ] Testar: `"1"`, `"2+3"`, `"3*4"`, `"3+4*5"`, `"(3+4)*5"`

---

## 💾 COLA DE BOLSO
```
┌───────────────────────────────────────┐
│ AMP: Add → Multi → Primary            │
│                                       │
│ TEMPLATE (Add/Multi):                 │
│   left = superior()                   │
│   while (meu_op)                      │
│     right = superior()                │
│     tmp = {TIPO, 0, left, right}      │
│     left = new_node(tmp)              │
│   return left                         │
│                                       │
│ PRIMARY (especial):                   │
│   if ('(') parse_add()                │
│   if (digit) {VAL, n, NULL, NULL}     │
│   else unexpected()                   │
│                                       │
│ CORREÇÃO: accept() precisa **s == c   │
└───────────────────────────────────────┘

🎯 ESTRATÉGIA DE ESTUDO

Decore AMP - escreva 10x no papel
Decore o Template - escreva 5x
Aplique: faça parse_multi mudando só 3 coisas
Aplique: faça parse_add mudando só 3 coisas
Primary: escreva 3x (é único diferente)
Teste mentalmente: trace "3+4*5" no papel
