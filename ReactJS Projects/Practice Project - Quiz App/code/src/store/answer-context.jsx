import { createContext, useReducer } from 'react';
import { QUESTION } from '../questions.js';


export const AnswerContext = createContext({
    selected: false,
    correct: undefined,
    selectedAnswers: [],
    checkAnswers: [],
    selectItem: () => { },
    skipItem: () => { },
    checkItem: () => { },
});

function answerStateReducer(state, action) {
    if (action.type === 'SELECT') {
        const updatedAnswers = [...state.selectedAnswers];
        updatedAnswers.push(action.text);
        //console.log(state.selectedAnswers);

        return {
            ...state,
            selected: true,
            selectedAnswers: updatedAnswers,
        };        
    }

    if (action.type === 'CHECK') {
        const updatedAnswers = [...state.checkAnswers];
        if (QUESTION[state.selectedAnswers.length - 1].answers[0] === state.selectedAnswers[state.selectedAnswers.length - 1]) {
            updatedAnswers.push('correct');
            //console.log(QUESTION[state.selectedAnswers.length - 1].answers[0]);
            //console.log(state.selectedAnswers[state.selectedAnswers.length - 1]);
            console.log(updatedAnswers);
            return {
                ...state,
                selected: false,
                checkAnswers: updatedAnswers,
            };
        } else {
            updatedAnswers.push('wrong');
            //console.log(QUESTION[state.selectedAnswers.length - 1].answers[0]);
            //console.log(state.selectedAnswers[state.selectedAnswers.length - 1]);
            console.log(updatedAnswers);
            return {
                ...state,
                selected: false,
                checkAnswers: updatedAnswers,
            };
        }       
    }

    if (action.type === 'SKIP') {
        const updatedCAnswers = [...state.checkAnswers];
        const updatedSAnswers = [...state.selectedAnswers];
        updatedSAnswers.push('');
        updatedCAnswers.push('skip');

        console.log(updatedCAnswers);
        return {
            ...state,
            selected: false,
            selectedAnswers: updatedSAnswers,
            checkAnswers: updatedCAnswers,
        };
    }

    return state;
}

export default function AnswerContextProvider({ children }) {
    const [answerState, answerStateDispatch] = useReducer(
        answerStateReducer,
        {
            selected: false,
            correct: undefined,
            selectedAnswers: [],
            checkAnswers: [],
        }
    );

    function handleAnswerCheck() {
        answerStateDispatch({
            type: 'CHECK',            
        });
    }

    function handleAnswerSkip() {
        answerStateDispatch({
            type: 'SKIP',
        });
    }

    function handleAnswerSelect(answer) {
        answerStateDispatch({
            type: 'SELECT',
            text: answer,
        });
    }

    const ctxValue = {
        selected: answerState.selected,
        correct: answerState.correct,
        selectedAnswers: answerState.selectedAnswers,
        checkAnswers: answerState.checkAnswers,
        selectItem: handleAnswerSelect,
        skipItem: handleAnswerSkip,
        checkItem: handleAnswerCheck,
        };

    return (
        <AnswerContext.Provider value={ctxValue}>{children}</AnswerContext.Provider>
    );
}