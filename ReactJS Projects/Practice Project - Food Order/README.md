# Food Order App

**Live demo**: https://practice-project---food-4decd.web.app/

A full-stack food ordering web application built with **React 18**, **React Router**, and a **Firebase** backend.

## What it does

- Displays a menu of available meals fetched from a remote API
- Allows users to add/remove items from a shopping cart
- Shows a cart modal with item quantities and total price
- Handles checkout with a form that validates user input
- Submits orders to a backend (Firebase) and confirms successful placement

## Key React concepts demonstrated

| Concept | Where used |
|---------|-----------|
| Custom hooks | `useFetch` — reusable hook for all HTTP GET requests; `useInput` — form field validation hook |
| Context API | `order-cart-context.jsx` — global cart state (items, quantities, totals) shared across the component tree |
| HTTP & side effects | `http.js` module with `fetch`-based helpers; data fetched on mount via `useEffect` |
| React Router DOM 6 | Multi-page navigation between menu, cart, and checkout views |
| Form handling | Controlled inputs, validation feedback, and submission with loading/error states |
| Firebase backend | Cloud Firestore for storing and reading order data |

## Tech stack

- React 18.2
- React Router DOM 6.21
- Firebase (Firestore)
- Vite 4
- dotenv (environment variables)
- Node.js backend (`backend/`)

## Running locally

```bash
# Frontend
cd code
npm install
npm run dev

# Backend (separate terminal)
cd code/backend
npm install
npm start
```

Create a `.env` file in `code/` with your Firebase credentials before starting.
