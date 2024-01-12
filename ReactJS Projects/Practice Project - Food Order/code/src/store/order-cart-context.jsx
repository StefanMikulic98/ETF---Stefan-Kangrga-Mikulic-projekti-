import { createContext, useReducer } from 'react';

export const CartContext = createContext({
    orders: [],    
    addItemToCart: () => { },
    updateItemQuantity: () => { },
    clearCart: () => { },
});

function orderCartReducer(state, action) {
    if (action.type === 'ADD_ITEM') {
        const updatedOrders = [...state.orders];
       
        const existingCartOrdersIndex = updatedOrders.findIndex(
            (item) => item.id === action.payload.id
        );       
        const existingOrderItem = updatedOrders[existingCartOrdersIndex];        

        if (existingOrderItem) {
            const updatedOrder = {
                ...existingOrderItem,
                quantity: existingOrderItem.quantity + 1,
            };
            updatedOrders[existingCartOrdersIndex] = updatedOrder;
            console.log(updatedOrders);
        } else {           
            updatedOrders.push({
                ...action.payload,
                quantity: 1,
            });
            console.log(updatedOrders);
        }

        return {
            ...state,
            orders: updatedOrders,
        };
    }

    if (action.type === 'UPDATE_ITEM') {        
        const updatedOrders = [...state.orders];
        const existingCartOrdersIndex = updatedOrders.findIndex(
            (item) => item.id === action.payload.productId
        );

        const existingOrderItem = {
            ...updatedOrders[existingCartOrdersIndex],
        };      

        existingOrderItem.quantity += action.payload.amount;

        if (existingOrderItem.quantity <= 0) {
            updatedOrders.splice(existingCartOrdersIndex, 1);
        } else {
            updatedOrders[existingCartOrdersIndex] = existingOrderItem;
        }
        console.log(updatedOrders);
        return {
            ...state,
            orders: updatedOrders,
        };
    }

    if (action.type === 'CLEAR') {
        return {
            ...state,
            orders: [],
        };
    }
    return state;
}

export default function CartContextProvider({ children }) {
    const [orderCartState, orderCartDispatch] = useReducer(
        orderCartReducer,
        {
            orders: [],
        }
    );

    function handleAddItemToCart(item) {
        orderCartDispatch({
            type: 'ADD_ITEM',
            payload: item,
        });
    }

    function handleUpdateCartItemQuantity(productId, amount) {
        orderCartDispatch({
            type: 'UPDATE_ITEM',
            payload: {
                productId,
                amount
            }
        });
    }

    function handleClearCart() {
        orderCartDispatch({
            type: 'CLEAR',           
        });
    }

    const ctxValue = {
        orders: orderCartState.orders,       
        addItemToCart: handleAddItemToCart,
        updateItemQuantity: handleUpdateCartItemQuantity,
        clearCart: handleClearCart,
    };

    return (
        <CartContext.Provider value={ctxValue}>{children}</CartContext.Provider>
    );
}
