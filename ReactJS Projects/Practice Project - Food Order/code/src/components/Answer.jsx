export default function Answer({ onCloseAnswer }) {

    return (
        <div className="cart">
            <h2>Success</h2>
            
            <p>
                Your Order was submitted successfully.   
            </p>
            <p>
                We will get back to you with more details via email within the next few minutes.
            </p>
            <p className="modal-actions">
                <button className="button" onClick={onCloseAnswer}>Checkout</button>
            </p>
        </div>
    );
}