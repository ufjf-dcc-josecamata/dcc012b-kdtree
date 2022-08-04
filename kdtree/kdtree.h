#ifndef KDTREE_H__
#define KDTREE_H__

#include "point.h" 

/**
 * @brief Classe KDTreeNode
 * @details Esta classe representa um nó de uma KdTree.
 *   Um nó da árvore KDTree armazena os seguintes campos:
 *     - Ponto de dimensão n
 *     - Ponteiro para o nó esquerdo
 *     - Ponteiro para o nó direito
 *     - indice do eixo que o nó está dividido
 */

template <typename T, size_t dim> class KDTree; 
template <typename T, size_t dim>
class KDTreeNode 
{
    friend class KDTree<T, dim>;
    public:
        KDTreeNode(const Point<T,dim>& point):
             _point(point), 
             _left(nullptr), 
             _right(nullptr), 
             _axis(0)
        {}
        KDTreeNode(const Point<T,dim>& point, int axis): 
            _point(point), 
            _left(nullptr), 
            _right(nullptr), 
            _axis(axis)
        {}
        int get_axis() const 
        {
            return _axis; 
        }
    private:
        Point<T, dim>       _point;  // Ponto de dimensão n
        int                  _axis;  // Eixo que o nó está dividido
        KDTreeNode<T, dim>*  _left;  // Ponteiro para o nó esquerdo
        KDTreeNode<T, dim>*  _right; // Ponteiro para o nó direito
};


/**
 * @brief Classe KDTree
 * @details Esta classe representa uma árvore KDTree. 
 *  Uma árvore KDTree armazena os seguintes campos:
 *      - um ponteiro para o nó raiz
 *      - o numero de nos da árvore
 */

template <typename T, size_t dim>
class KDTree 
{
    public:
        // Construtores da classe KDTree.
        KDTree();
  
        // Destrutor da classe KDTree.
        ~KDTree();

        //  insere um ponto na árvore.
        void insert(const Point<T,dim>& point);

        // remove todos os pontos da arvore.
        void clear();

        // imprime a arvore na tela.
        void print() const;

        // retorna o numero de nos da arvore.
        size_t size() const;

        // retorna verdadeiro se a arvore estiver vazia.
        bool empty() const;

        // verifica se um ponto está na arvore.    
        bool contains(const Point<T,dim>& point) const;

        // retorna o ponto de menor distancia ao ponto passado como parametro.
        Point<T,dim> nearest(const Point<T,dim>& point);

    private:
        //  Funções auxiliares.
        void insert(KDTreeNode<T, dim>* node, const Point<T,dim>& point);
        void clear(KDTreeNode<T, dim>* node);
        void print(KDTreeNode<T, dim>* node) const;
        bool contains(KDTreeNode<T, dim>* node, const Point<T,dim>& point) const;
        void nearest(KDTreeNode<T, dim>* node, const Point<T,dim>& point);

        // Atributos da classe KDTree.
        KDTreeNode<T, dim>* _root;
        KDTreeNode<T, dim>* _best;
        size_t _size;
};


template <typename T, size_t dim>
void KDTree<T, dim>::insert(const Point<T,dim>& p)
{
    // 1. Se a arvore estiver vazia, cria um novo nó raiz com ponto p.
    // 2. Se a arvore não estiver vazia, chama a função insert inserido o 
    //    o ponto p a partir da raiz.
    if(_root == nullptr)
    {
        _root = new KDTreeNode<T, dim>(p);
        _size++;
    }
    else
    {
        insert(_root, p);
    }
}


// TODO: Implementar o método insert.
template <typename T, size_t dim>
void KDTree<T, dim>::insert(KDTreeNode<T, dim>* node, const Point<T,dim>& point)
{
    // 1. Se node for null, retorne
    // 2. Caso contrario, obtenha o eixo que o nó atual está dividido.
    // 3. Compare o valor do eixo do ponto p com o valor do eixo do nó atual.
    // 4. Se o valor do eixo do ponto p for menor que o valor do eixo do nó atual,
    //    então o ponto p deve ser inserido na subárvore esquerda do nó atual.
    //     4.1. Se a subarvore esquerda for null, crie um novo no com point e aponte para esta subarvore.
    //     4.2  se não, chame recursivamente esta função para subarvore esquerda.
    // 5. Caso contrário, o ponto p deve ser inserido na subárvore direita do nó atual
    //     5.1. Se a subarvore direita for null, crie um novo no com point e aponte para esta subarvore.
    //     5.2  se não, chame recursivamente esta função para subarvore direita.
    
}

// Cria uma arvore vazia
template <typename T, size_t dim>
KDTree<T, dim>::KDTree()
{
    _root = nullptr;
    _size = 0;
}

// Destrutor
template <typename T, size_t dim>
KDTree<T, dim>::~KDTree()
{
    clear();
}


template <typename T, size_t dim>
void KDTree<T, dim>::clear()
{
    clear(_root);
    _root = nullptr;
    _size = 0;
}

// Desaloca a subarvore enraizada por node
template <typename T, size_t dim>
void KDTree<T, dim>::clear(KDTreeNode<T, dim>* node)
{
    if (node == nullptr) {
        return;
    }
    clear(node->_left);
    clear(node->_right);
    delete node;
}

template <typename T, size_t dim>
void KDTree<T, dim>::print() const
{
    print(_root);
}

template <typename T, size_t dim>
void KDTree<T, dim>::print(KDTreeNode<T, dim>* node) const
{
    if (node == nullptr) {
        return;
    }
    print(node->_left);
    std::cout << node->_point << std::endl;
    print(node->_right);
}

template <typename T, size_t dim>
size_t KDTree<T, dim>::size() const
{
    return _size;
}

template <typename T, size_t dim>
bool KDTree<T, dim>::empty() const
{
    return _size == 0;
}

template <typename T, size_t dim>
bool KDTree<T, dim>::contains(const Point<T,dim>& point) const
{
    return contains(_root, point);
}

template <typename T, size_t dim>
bool KDTree<T, dim>::contains(KDTreeNode<T, dim>* node, const Point<T,dim>& point) const
{
    if (node == nullptr) {
        return false;
    }
    int axis = node->get_axis();
    if (point.get(axis) < node->_point.get(axis)) {
        return contains(node->_left, point);
    } else if (point.get(axis) > node->_point.get(axis)) {
        return contains(node->_right, point);
    } else {
        return true;
    }
}

// Obtem o ponto mais próximo de point 
template <typename T, size_t dim>
Point<T, dim> KDTree<T, dim>::nearest(const Point<T,dim>& point)
{
   
    this->_best = nullptr;
    nearest(_root, point);
    return _best->_point;
}

template <typename T, size_t dim>
void KDTree<T, dim>::nearest(KDTreeNode<T, dim>* node, const Point<T,dim>& point) 
{

    if (node == nullptr) {
        return;
    }
    double d_best = (this->_best==nullptr)? MAXFLOAT:_best->_point.get_distance(point);
    double d      = node->_point.get_distance(point);
    
    if (this->_best == nullptr || d < d_best) {
        this->_best = node;
        d_best = d;
    }

    if(d_best == 0) {
        return;
    }

    int idx = node->get_axis();
    int next_idx = (idx + 1) % dim;
    double dx = node->_point.get(idx) - point.get(idx);
    nearest(dx > 0 ? node->_left : node->_right, point);
    if ( (dx * dx) >= d_best)
        return; 
    nearest(dx > 0 ? node->_right: node->_left, point);
}



#endif /* KDTREE_H__ */
