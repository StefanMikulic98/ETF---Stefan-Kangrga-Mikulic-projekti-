import { useState, useEffect } from 'react';

export default function ProgressBar({ timer, onTimeout, mode}) {
    const [remainingTime, setRemainingTime] = useState(timer);
    
    useEffect(() => {
        const timeout = setTimeout(onTimeout, timer);
        //console.log('TIMEOUT');    
        return () => {
            //console.log('CLEAR TIMEOUT');
            clearInterval(timeout);
        };
    }, [timer, onTimeout]);

    useEffect(() => {
        const interval = setInterval(() => {
            //console.log('INTERVAL');
            setRemainingTime((prevTime) => prevTime - 100);
        }, 100);

        return () => {
            //console.log('CLEAR INTERVAL');
            clearInterval(interval);
        };
    }, []);

    return <progress id="question-time" value={remainingTime} max={timer} className={mode} />;
}