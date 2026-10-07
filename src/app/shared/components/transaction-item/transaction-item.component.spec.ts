import { ComponentFixture, TestBed } from '@angular/core/testing';
import { TransactionItemComponent } from './transaction-item.component';

describe('TransactionItemComponent', () => {
  let component: TransactionItemComponent;
  let fixture: ComponentFixture<TransactionItemComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [TransactionItemComponent],
    }).compileComponents();

    fixture = TestBed.createComponent(TransactionItemComponent);

    component = fixture.componentInstance;

    component.transaction = {
      title: 'Spotify',
      category: 'Subscription',
      amount: -9.99,
      icon: 'music_note',
    };

    fixture.detectChanges();
  });

  it('should apply negative class', () => {
    const amount =
      fixture.nativeElement.querySelector('.amount');

    expect(amount.classList).toContain('negative');
  });
});
