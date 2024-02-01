import Input from './Input.jsx';
import { isEmail, isNotEmpty, hasMaxLength, isStreet } from '../util/validation.js';
import { useInput } from '../hooks/useInput.js';
import { useContext, useState } from 'react';
import { CartContext } from '../store/order-cart-context.jsx';
import { currencyFormatter } from '../util/formatting.js';

let globalError = false
export default function Checkout({ onCloseCheckout, onSelectAnswer }) {
    const { orders } = useContext(CartContext);
    const [errorSubmit, setErrorSubmit] = useState({
        error: false,
        message: '',
    });
    const totalPrice = orders.reduce(
        (total, item) => total + item.price * item.quantity,
        0
    );
    const {
        value: fullName,
        handleInputChange: handleFullNameChange,
        handleInputBlur: handleFullNameBlur,
        hasError: fullNameHasError,
    } = useInput('', (value) => isNotEmpty(value));

    const {
        value: emailValue,
        handleInputChange: handleEmailChange,
        handleInputBlur: handleEmailBlur,
        hasError: emailHasError,
    } = useInput('', (value) => isEmail(value) && isNotEmpty(value));

    const {
        value: streetValue,
        handleInputChange: handleStreetChange,
        handleInputBlur: handleStreetBlur,
        hasError: streetHasError,
    } = useInput('', (value) => isStreet(value) && isNotEmpty(value));

    const {
        value: postalCodeValue,
        handleInputChange: handlePostalCodeChange,
        handleInputBlur: handlePostalCodeBlur,
        hasError: postalCodeHasError,
    } = useInput('', (value) => hasMaxLength(value, 10));

    const {
        value: cityValue,
        handleInputChange: handleCityChange,
        handleInputBlur: handleCityBlur,
        hasError: cityHasError,
    } = useInput('', (value) => isNotEmpty(value));

    async function handleSubmit(event) {
        event.preventDefault();

        try {
            const response = await fetch('https://practice-project-food-order.onrender.com/orders', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    order: {
                        items: orders,
                        customer: {
                            name: fullName,
                            email: emailValue,
                            street: streetValue,
                            ['postal-code']: postalCodeValue,
                            city: cityValue
                        }
                    }
                })
            })
            const resData = await response.json();

            if (response.ok) { 
                globalError = false;
            } else {        
                throw new Error(
                    resData.message || 'Something went wrong, failed to send request.'
                );                
            }
        } catch (error) {   
            setErrorSubmit({
                error: true,
                message: error.message || 'Something went wrong!',
            });
            globalError = true;
        }       


        if (globalError || emailHasError || streetHasError || fullNameHasError || postalCodeHasError || cityHasError) {            
            onCloseCheckout;
            return;
        }

        console.log(fullName, emailValue, streetValue, postalCodeValue, cityValue);
        setErrorSubmit({
            error: false,
            message: '',
        });
        onSelectAnswer();     
        return;
    }

    return (
        <form onSubmit={handleSubmit}>
            <h2>Checkout</h2>
            <p> Total amount: {currencyFormatter.format(totalPrice)}</p>
                
            <div className="control">
                <Input
                    label="Full Name"
                    id="name"
                    type="text"
                    name="full-name"
                    onBlur={handleFullNameBlur}
                    onChange={handleFullNameChange}
                    value={fullName}
                    error={fullNameHasError && 'Please enter a full name!'}
                />
            </div>

            <div className="control">
                <Input
                    label="E-Mail Address"
                    id="email"
                    type="email"
                    name="email"
                    onBlur={handleEmailBlur}
                    onChange={handleEmailChange}
                    value={emailValue}
                    error={emailHasError && 'Please enter a valid email!'}
                />
            </div>

            <div className="control">
                <Input
                    label="Street"
                    id="street"
                    //type="text"
                    name="street"
                    onBlur={handleStreetBlur}
                    onChange={handleStreetChange}
                    value={streetValue}
                    error={streetHasError && 'Please enter a valid street!'}
                />
            </div>

            <div className="control-row">
                <Input
                    label="Postal Code"
                    id="postal-code"
                    type="number"
                    name="postal-code"
                    onBlur={handlePostalCodeBlur}
                    onChange={handlePostalCodeChange}
                    value={postalCodeValue}
                    error={postalCodeHasError && 'Please enter a valid postal code!'}
                />

                <Input
                    label="City"
                    id="city"
                    type="text"
                    name="city"
                    onBlur={handleCityBlur}
                    onChange={handleCityChange}
                    value={cityValue}
                    error={cityHasError && 'Please enter a city!'}
                />
            </div>
            {errorSubmit.error && (<div className="error">
                <h2>Error</h2>
                <p >{errorSubmit.message}</p>
            </div>) }
            <p className="modal-actions">
                <button className="text-button" type="button" onClick={onCloseCheckout}>Close</button>
                <button className="button" type="submit">Checkout</button>
            </p>

        </form>
        );
}