import logo from '../assets/logo.jpg';
import CartModal from './CartModal.jsx';
import Cart from './Cart.jsx';
import Checkout from './Checkout.jsx';
import Answer from './Answer.jsx';
import { useState, useContext } from 'react';
import { CartContext } from '../store/order-cart-context.jsx';


export default function Header() {
    const [modalIsOpen, setModalIsOpen] = useState(false);
    const [typeCart, setTypeCart] = useState('close');
    const type = ['close', 'cart', 'checkout', 'answer']
    const { orders, clearCart } = useContext(CartContext);

    const cartQuantity = orders.reduce((total, item) => {
        return total + item.quantity;
    }, 0);

    //console.log(typeCart);

    function handleOpenTypeCart() {
        const currentTypeCartIndex = type.findIndex(
            (item) => item === typeCart
        );
        
        if (currentTypeCartIndex === type.length-1) {
            const nextType = 'close';
            clearCart();
            setTypeCart(nextType);
            setModalIsOpen(false);
        } else {
            const nextType = type[currentTypeCartIndex + 1];
            setTypeCart(nextType);
            setModalIsOpen(true);
        }
        
    }  

    function handleCloseTypeCart() {
        const currentTypeCartIndex = type.findIndex(
            (item) => item === typeCart
        );       
        
        if (currentTypeCartIndex === 1 || currentTypeCartIndex === 0) {
            const nextType = 'close';
            setTypeCart(nextType);
            setModalIsOpen(false);
        } else {
            const nextType = type[currentTypeCartIndex - 1];
            setTypeCart(nextType);
            
        }
        
    }

    return (
        <>
            <CartModal open={modalIsOpen} onClose={handleCloseTypeCart}>
                {(typeCart === 'cart') && <Cart onCloseOrder={handleCloseTypeCart} onSelectCheckout={handleOpenTypeCart} />}               
                {(typeCart === 'checkout') && <Checkout onCloseCheckout={handleCloseTypeCart} onSelectAnswer={handleOpenTypeCart} />}
                {(typeCart === 'answer') && <Answer onCloseAnswer={handleOpenTypeCart} />}
            </CartModal>
            <header id="main-header">
                <div id="title">
                    <img src={logo} alt="A restaurant" />
                    <h1>ReactFood</h1>
                </div> 
                <nav>
                    <button className="text-button" onClick={handleOpenTypeCart}>Cart ({cartQuantity})</button>           
                </nav>
            </header>
        </>
    );
}