# Quiz App

**Live demo**: https://practice-project---quiz-app.web.app/

A browser-based multiple-choice quiz application built with **React 18** and **Vite**.

## What it does

- Presents a series of questions one at a time with four answer choices each
- Tracks progress with a visual progress bar
- Highlights correct and incorrect answers after selection
- Displays a results summary screen at the end showing how the user scored

## Key React concepts demonstrated

| Concept | Where used |
|---------|-----------|
| Context API | `answer-context.jsx` — shares quiz state (selected answers, score) across components without prop drilling |
| `useState` / `useReducer` | Managing current question index, selected answer, and quiz completion state |
| Conditional rendering | Showing question view vs. summary screen; highlighting correct/wrong answers |
| Component composition | `Quiz → Question → Answer`, `ProgressBar`, `Summary` as separate focused components |
| Vite build tooling | Fast dev server and optimised production build |

## Tech stack

- React 18.2
- Vite 4
- ESLint (React rules)

## Running locally

```bash
cd code
npm install
npm run dev
```

Open `http://localhost:5173` in your browser.
