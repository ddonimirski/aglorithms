use heap::{Data, Heap, Node, Priority};

#[cfg(test)]
mod heap_tests {

    use super::*;
    type Item = i32;

    #[test]
    fn is_empty() {
        let heap = Heap::<Item>::new();
        assert!(heap.is_empty());

        let mut heap = Heap::<Item>::new();

        const VALUE_1: Item = 1;
        const PRIORITY_0: Priority = 0;

        heap.insert(VALUE_1, PRIORITY_0);
        assert!(!heap.is_empty());
        assert_eq!(heap.len(), 1);
    }

    #[test]
    fn peek() {
        let mut heap = Heap::<Item>::new();

        const VALUE_4: Item = 4;
        const PRIORITY_4: Priority = 4;
        heap.insert(VALUE_4, PRIORITY_4);
        assert_eq!(heap.peek(), 4);

        const VALUE_2: Item = 2;
        const PRIORITY_2: Priority = 2;
        heap.insert(VALUE_2, PRIORITY_2);
        assert_eq!(heap.peek(), 2);

        const VALUE_3: Item = 3;
        const PRIORITY_3: Priority = 3;
        heap.insert(VALUE_3, PRIORITY_3);
        assert_eq!(heap.peek(), 2);

        const VALUE_1: Item = 1;
        const PRIORITY_1: Priority = 1;
        heap.insert(VALUE_1, PRIORITY_1);
        assert_eq!(heap.peek(), 1);
    }

    #[test]
    fn top() {
        let mut heap = Heap::<Item>::new();

        const VALUE_4: Item = 4;
        const PRIORITY_4: Priority = 4;
        heap.insert(VALUE_4, PRIORITY_4);

        const VALUE_2: Item = 2;
        const PRIORITY_2: Priority = 2;
        heap.insert(VALUE_2, PRIORITY_2);

        const VALUE_3: Item = 3;
        const PRIORITY_3: Priority = 3;
        heap.insert(VALUE_3, PRIORITY_3);

        const VALUE_1: Item = 1;
        const PRIORITY_1: Priority = 1;
        heap.insert(VALUE_1, PRIORITY_1);

        let v = heap.top();
        assert_eq!(v, VALUE_1);
        let v = heap.top();
        assert_eq!(v, VALUE_2);
        let v = heap.top();
        assert_eq!(v, VALUE_3);
        let v = heap.top();
        assert_eq!(v, VALUE_4);
    }

    #[test]
    fn remove() {
        // todo!();
    }

    #[test]
    fn update() {
        // todo!();
    }

    #[test]
    fn heapify() {
        type Item = i32;
        const D: heap::Index = 2;

        let mut data: Data<Item> = vec![
            Node {
                value: 1,
                priority: 1,
            },
            Node {
                value: 2,
                priority: 2,
            },
            Node {
                value: 3,
                priority: 3,
            },
            Node {
                value: 4,
                priority: 4,
            },
            Node {
                value: 5,
                priority: 5,
            },
            Node {
                value: 6,
                priority: 0,
            },
        ];

        heap::heapify::<Item, D>(&mut data);

        let expected: Data<Item> = vec![
            Node {
                value: 6,
                priority: 0,
            },
            Node {
                value: 2,
                priority: 2,
            },
            Node {
                value: 1,
                priority: 1,
            },
            Node {
                value: 4,
                priority: 4,
            },
            Node {
                value: 5,
                priority: 5,
            },
            Node {
                value: 3,
                priority: 3,
            },
        ];

        assert_eq!(
            expected.iter().zip(&data).filter(|&(a, b)| a == b).count(),
            expected.len()
        );
    }

    #[test]
    fn from() {
        type Item = i32;

        {
            const D: heap::Index = 2;

            let data: Data<Item> = vec![
                Node {
                    value: 1,
                    priority: 1,
                },
                Node {
                    value: 2,
                    priority: 2,
                },
                Node {
                    value: 3,
                    priority: 3,
                },
                Node {
                    value: 4,
                    priority: 4,
                },
                Node {
                    value: 5,
                    priority: 5,
                },
                Node {
                    value: 6,
                    priority: 0,
                },
            ];

            let mut heap = Heap::<Item, D>::new().from(data);

            assert_eq!(heap.top(), 6);
            assert_eq!(heap.top(), 1);
            assert_eq!(heap.top(), 2);
            assert_eq!(heap.top(), 3);
            assert_eq!(heap.top(), 4);
            assert_eq!(heap.top(), 5);
        }
        {
            const D: heap::Index = 3;

            let data: Data<Item> = vec![
                Node {
                    value: 1,
                    priority: 1,
                },
                Node {
                    value: 2,
                    priority: 2,
                },
                Node {
                    value: 3,
                    priority: 3,
                },
                Node {
                    value: 4,
                    priority: 4,
                },
                Node {
                    value: 5,
                    priority: 5,
                },
                Node {
                    value: 6,
                    priority: 0,
                },
            ];

            let mut heap = Heap::<Item, D>::new().from(data);

            assert_eq!(heap.top(), 6);
            assert_eq!(heap.top(), 1);
            assert_eq!(heap.top(), 2);
            assert_eq!(heap.top(), 3);
            assert_eq!(heap.top(), 4);
            assert_eq!(heap.top(), 5);
        }
    }
}
