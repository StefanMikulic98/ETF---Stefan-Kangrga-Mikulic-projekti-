import { useContext } from 'react';
import { CartContext } from '../store/order-cart-context.jsx';
import { currencyFormatter } from '../util/formatting.js';

export default function Cart({ onCloseOrder, onSelectCheckout }) {
    const { orders, updateItemQuantity } = useContext(CartContext);

    const totalPrice = orders.reduce(
        (total, item) => total + item.price * item.quantity,
        0
    );
    const formattedTotalPrice = `$${totalPrice.toFixed(2)}`;
    const cartQuantity = orders.reduce((total, item) => {
        return total + item.quantity;
    }, 0);

    let modalActions = (
        <p className="modal-actions">
            <button className="text-button" type="reset" onClick={onCloseOrder}>Close</button>
         </p>
    );

    if (cartQuantity > 0) {
        modalActions = (
            <p className="modal-actions">
                <button className="text-button" onClick={onCloseOrder}>Close</button>
                <button className="button" onClick={onSelectCheckout}>Go to Checkout</button>
            </p>
        );
    }

    return (
        <div className="cart">
            <h2>Your Cart</h2>
            {orders.length === 0 && <p>No items in cart!</p>}
            {orders.length > 0 && (
                <ul>
                    {orders.map((order) => {
                        //const formattedPrice = `$${order.price.toFixed(2)}`;

                        return (
                            <li key={order.id} className="cart-item">
                                <p>
                                    {order.name} - {order.quantity} x {currencyFormatter.format(order.price)}
                                </p>
                                <div className="cart-item-actions">
                                    <button onClick={() => updateItemQuantity(order.id, -1)}>
                                        -
                                    </button>
                                    <span>{order.quantity}</span>
                                    <button onClick={() => updateItemQuantity(order.id, 1)}>
                                        +
                                    </button>
                                </div>
                            </li>
                        );
                    })}
                </ul>
            )}
            <p className="cart-total">
                <strong>{formattedTotalPrice}</strong>
            </p>
            {modalActions}
        </div>
    );
}